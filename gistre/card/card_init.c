#include <linux/errno.h>
#include <linux/of.h>

#include "card.h"
#include "card_fops.h"

static struct cardio_dev *cardio_create(void)
{
    struct cardio_dev *dev = kmalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev) {
        return NULL;
    }

    dev->cdev.owner = THIS_MODULE;
    cdev_init(&dev->cdev, &cardio_fops);

    return dev;
}

__init int cardio_init(void)
{
    pr_info("Hello, GISTRE card !\n");

    dev_t dev;
    int ret;
    const char devname[] = "cardio";

    /* Allocate major */
    ret = alloc_chrdev_region(&dev, 0, 1, devname);
    if (ret < 0) {
        pr_info("Failed to allocate major\n");
        return 1;
    } else {
        major = MAJOR(dev);
        pr_info("Got major %d\n", major);
    }

    /* Register char device */
    cio_dev = cardio_create();
    if (!cio_dev) {
        pr_err("Failed to init pingpong_dev\n");
        return -ENOMEM;
    }

    if (cdev_add(&cio_dev->cdev, dev, 1) < 0) {
        pr_err("Failed to register char device\n");
        return -ENOMEM;
    }

    struct device_node *device_node;
    device_node = of_find_node_by_name(of_root, MFRC522_NAME);
    if (!device_node) {
        pr_err("%s: Did not find node %s...\n", __func__, MFRC522_NAME);
        return 1;
    }

    u32 version;
    if (of_property_read_u32(device_node, MFRC522_PROP, &version)) {
        pr_err("%s: Did not find property \"%s\"\n", __func__, MFRC522_PROP);
        return 1;
    } else {
        pr_info("%s: \"%s\": %u\n", __func__, MFRC522_PROP, version);
    }

    return 0;
}