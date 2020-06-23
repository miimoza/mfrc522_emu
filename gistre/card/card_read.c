#include <linux/regmap.h>
#include <linux/uaccess.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card_fops.h"

ssize_t card_read(struct file *file, char __user *buf, size_t len,
                    loff_t *off /* unused */)
{
    pr_info("[READ]\n");




    struct pingpong_dev *dev;

	pr_info("%s()\n", __func__);

	dev = (struct pingpong_dev *)file->private_data;
	if (cdev->buffer_len) {
		if (copy_to_user(buf, cdev->buffer, cdev->buffer_len)) {
			pr_err("Failed to copy data to user\n");
			return -EFAULT;
		}
	}
	else {
		len = 0;
	}

	return len;
}
