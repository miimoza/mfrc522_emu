#include <linux/cdev.h>

#include "card.h"

static void cardio_destroy(struct cardio_dev *dev)
{
    cdev_del(&dev->cdev);
    kfree(dev);
}

__exit void cardio_exit(void)
{
    dev_t dev;

    dev = MKDEV(major, 0);
    cardio_destroy(cio_dev);
    unregister_chrdev_region(dev, 1);

    pr_info("Goodbye, GISTRE card !\n");
}
