#include <linux/regmap.h>
#include <linux/uaccess.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card_fops.h"
#include "card.h"

ssize_t card_read(struct file *file, char __user *buf, size_t len,
                    loff_t *off /* unused */)
{
	if (c_dev->buffer_len) {
        len = min(len, c_dev->buffer_len);
		if (copy_to_user(buf, c_dev->buffer, c_dev->buffer_len)) {
			pr_err("Failed to copy data to user\n");
			return -EFAULT;
		}
        len = c_dev->buffer_len;
        c_dev->buffer_len = 0;
        c_dev->buffer[0] = '\0';
	}
	else {
		len = 0;
	}

	return len;
}
