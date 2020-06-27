#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <uapi/asm-generic/ioctl.h>

/*
 * Metadata
 */

MODULE_AUTHOR("Geoffrey Le Gourriérec");
MODULE_DESCRIPTION("A driver that logs its contents on demand.");
MODULE_LICENSE("GPL v2");

/*
 * Local definitions
 */

#define DI_BUF_SIZE	((size_t)256)

#define DI_IOCTL_TYPE    42
#define DI_IOCTL_DUMP    _IO(DI_IOCTL_TYPE, 0)

struct dumpioctl_dev {
	struct cdev cdev;
	/* Internal buffer */
	char buf[DI_BUF_SIZE];
	size_t buf_len;
};

/* Major will always be dynamically allocated */
static int major;
static struct dumpioctl_dev *di_dev;
static wait_queue_head_t wq_head;

/*
 * Character device file operations
 */

int di_open(struct inode *inode, struct file *file) {

	unsigned int i_major = imajor(inode);
	unsigned int i_minor = iminor(inode);

	pr_info("%s()\n", __func__);

	if (i_major != major) {
		pr_err("Invalid major %d, expected %d\n", i_major, major);
		return -EINVAL;
	}
	if (i_minor != 0) {
		pr_err("dump_on_ioctl driver only handles minor 0!\n");
		return -EINVAL;
	}

	file->private_data = di_dev;

	return 0;
}

int di_release(struct inode *inode /* unused */,
        struct file *file /* unused */) {

	pr_info("%s()\n", __func__);

	/* Nothing in particular to do */
	return 0;
}

ssize_t di_read(struct file *file, char __user *buf,
        size_t len, loff_t *off /* unused */) {

	struct dumpioctl_dev *dev;

	pr_info("%s()\n", __func__);

	dev = (struct dumpioctl_dev *)file->private_data;
	len = min(dev->buf_len, len);
	if (len == 0) {
		pr_info("Nothing to read...\n");
		return 0;
	}

	if (copy_to_user(buf, dev->buf, len)) {
		pr_err("copy_to_user() failed\n");
		return -EFAULT;
	}
	pr_info("Read %zu/%zu bytes\n", len, dev->buf_len);

	/* Destructive read, don't update offset */
	dev->buf_len = 0;

	return len;
}

ssize_t di_write(struct file *file, const char __user *buf,
        size_t len, loff_t *off) {

	struct dumpioctl_dev *dev;

	pr_info("%s()\n", __func__);

	dev = (struct dumpioctl_dev *)file->private_data;
	len = min(DI_BUF_SIZE-1 /* leave space for trailing nil */, len);
	if (len == 0) {
		pr_info("Nothing to write...\n");
		return 0;
	}

	/* Destructive write, don't update offset */
	if (copy_from_user(dev->buf, buf, len)) {
		pr_err("copy_from_user() failed\n");
		return -EFAULT;
	}
	dev->buf[len] = '\0';
	dev->buf_len  = len;
	pr_info("Wrote %zu/%zu bytes\n", len, DI_BUF_SIZE);

	/* In case someone is polling on us, wake them up */
	wake_up(&wq_head);

	return len;
}

long di_unlocked_ioctl(struct file *file, unsigned int cmd,
	unsigned long arg /* unused */) {

	struct dumpioctl_dev *dev;

	dev = file->private_data;

	switch (cmd) {
	case DI_IOCTL_DUMP:
		/* Dump our buffer's contents to kernel logs */
		pr_info("Buffer contents: %s\n", dev->buf);
		return 0;
	default:
		pr_info("Unknown ioctl command %d\n", cmd);
		return -EINVAL;
	}
}

unsigned int di_poll(struct file *file, poll_table *wait) {

	struct dumpioctl_dev *dev;

	dev = (struct dumpioctl_dev *)file->private_data;
	poll_wait(file, &wq_head, wait);

	if (dev->buf_len > 0) {
		return POLLIN | POLLRDNORM;
	}
	else {
		return 0;
	}
}

/*
 *  Init & Exit
 */

static struct file_operations di_fops = {
	.owner          = THIS_MODULE,
	.open           = di_open,
	.release        = di_release,
	.read           = di_read,
	.write          = di_write,
	.unlocked_ioctl = di_unlocked_ioctl,
	.poll           = di_poll,
	/* Other functions will use kernel defaults */
};

static struct dumpioctl_dev *di_create(void) {

	struct dumpioctl_dev *dev = kmalloc(sizeof(*dev), GFP_KERNEL);
	if (! dev) {
		return NULL;
	}

	dev->cdev.owner = THIS_MODULE;
	cdev_init(&dev->cdev, &di_fops);

	memset(dev->buf, 0, DI_BUF_SIZE);
	dev->buf_len = 0;

	return dev;
}

static void di_destroy(struct dumpioctl_dev *dev) {

	cdev_del(&dev->cdev);
	kfree(dev);
}

__exit
static void di_exit(void) {

	dev_t dev;

	pr_info("%s()\n", __func__);

	di_destroy(di_dev);

	dev = MKDEV(major, 0);
	unregister_chrdev_region(dev, 1);
}

__init
static int di_init(void) {

	dev_t dev;
	int ret;
	const char devname[] = "dump_on_ioctl";

	pr_info("%s()\n", __func__);

	/* Allocate major */
	ret = alloc_chrdev_region(&dev, 0, 1, devname);
	if (ret < 0) {
		pr_info("Failed to allocate major\n");
		return -EFAULT;
	}
	else {
		major = MAJOR(dev);
		pr_info("Got major %d\n", major);
	}

	/* Setup char device */
	di_dev = di_create();
	if (! di_dev) {
		pr_err("Failed to init di_dev\n");
		return -ENOMEM;
	}

	if (cdev_add(&di_dev->cdev, dev, 1) < 0) {
		pr_err("Failed to register char device\n");
		return -ENOMEM;
	}

	/* Setup wait queue for polling operations */
	init_waitqueue_head(&wq_head);

	return 0;
}

module_init(di_init);
module_exit(di_exit);
