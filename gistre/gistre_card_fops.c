#include "gistre_card_fops.h"

struct file_operations cardio_fops = {
 	.owner   = THIS_MODULE,
    .read    = cardio_read,
    .write   = cardio_write
 	/* Others functions are using the kernel's defaults */
};

ssize_t cardio_read(struct file *file, char __user *buf,
    size_t len, loff_t *off /* unused */)
{
    pr_info("reax\n");
    //regmap_read(struct regmap *map, unsigned int reg, unsigned int *val);
    return 0;
}

ssize_t cardio_write(struct file *file, const char __user *buf,
    size_t len, loff_t *off /* unused */)
{
    pr_info("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd\ntamere");
    //regmap_write(struct regmap *map, unsigned int reg, unsigned int val);
    return 0;
}
