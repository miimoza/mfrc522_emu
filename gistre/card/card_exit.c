#include <linux/slab.h>

#include "card.h"
#include "card_fops.h"

static void card_destroy(struct card_dev *dev)
{
    cdev_del(&dev->cdev);
    kfree(dev);
}

__exit void card_exit(void)
{
    dev_t dev;

    dev = MKDEV(major, 0);
    card_destroy(c_dev);
    unregister_chrdev_region(dev, 1);

    pr_info("Goodbye, GISTRE card !\n");
}

module_exit(card_exit);
