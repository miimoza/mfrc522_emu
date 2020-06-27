#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/uaccess.h>

/* Metadata
 */

MODULE_AUTHOR("Geoffrey Le Gourriérec");
MODULE_DESCRIPTION("An easy peasy misc character device");
MODULE_LICENSE("GPL v2");

/* Forward declarations
 */

ssize_t ppm_read(struct file *file /* unused */, char __user *buf,
    size_t len, loff_t *off /* unused */);
ssize_t ppm_write(struct file *file /* unused */, const char __user *buf,
    size_t len, loff_t *off /* unused */);

/* Globals
 */

#define PINGPONG_BUFSIZE sizeof("ping")

static const struct file_operations ppm_fops = {
	.owner = THIS_MODULE,
    .read  = ppm_read,
    .write = ppm_write,
	/* open() and release() misc implementations are fine */
};

static struct miscdevice ppm_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "ppm",
	.fops  = &ppm_fops,
	/* Other fields work well when left uninitialized */
};

static bool was_pinged;

/* Local definitions
 */

ssize_t ppm_read(struct file *file /* unused */, char __user *buf,
        size_t len, loff_t *off /* unused */) {

    /* This is pretty much the same thing as the original
     * pingpong implementation, except we don't handle individual
     * devices anymore.
     */
	pr_info("%s()\n", __func__);

	if (was_pinged) {
		/* Answer with a pong */
		const char pong[PINGPONG_BUFSIZE+1] = "pong";
		len = min(len, PINGPONG_BUFSIZE+1);

		if (copy_to_user(buf, pong, len)) {
			pr_err("Failed to copy data to user\n");
			return -EFAULT;
		}
		was_pinged = false;
	}
	else {
		/* Nothing to say */
		len = 0;
	}

	return len;
}

ssize_t ppm_write(struct file *file /* unused */, const char __user *buf,
    size_t len, loff_t *off /* unused */) {

    /* Like read(), this has nearly not changed.
     */
	char dev_buf[PINGPONG_BUFSIZE+1];

	pr_info("%s()\n", __func__);

	len = min(len, PINGPONG_BUFSIZE);
	memset(dev_buf, 0, PINGPONG_BUFSIZE+1);
	if (copy_from_user(dev_buf, buf, len)) {
		pr_err("Failed to copy user data\n");
		return -EFAULT;
	}

	if (strcmp(dev_buf, "ping") == 0) {
		pr_info("I was pinged!\n");
		was_pinged = true;
	}
	else {
		pr_info("I was not pinged; I received %s", dev_buf);
	}

	return len;
}

__init
static int ppm_init(void) {

	int ret;

	pr_info("%s()\n", __func__);

    /* For reference, the implementation of misc_register()
     * is located in drivers/char/misc.c
     *
     * A quick look at it shows us that is calls
     * device_create_with_groups(), just like we are about
     * to do in the next exercise, "statistics", creating
     * our class by hand.
     *
     * This calls cdev_add(), creates a node in devfs, etc.
     */
	ret = misc_register(&ppm_dev);
	if (ret) {
		pr_err("Failed to register misc device: %d\n", ret);
		return ret;
	}
	pr_info("Successfully got misc device %d\n", ppm_dev.minor);

    was_pinged = false;

	return 0;
}

__exit
static void ppm_exit(void) {

	pr_info("%s()\n", __func__);

	misc_deregister(&ppm_dev);
}

module_init(ppm_init);
module_exit(ppm_exit);
