#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#include "gistre_card_fops.h"
#include "mfrc522.h"
#include "mfrc522_emu.h"

#define MFRC522_NAME "mfrc522_emu"
#define MFRC522_PROP MFRC522_PROP_VERSION

// Metadata
MODULE_DESCRIPTION(
    "Cardio: a driver for the dummy \"Mfrc522\" iHaospace Kit RFID RC522, Module Carte de Lecteur MFRC-522 RF IC avec RFID Carte Puce Chip S50 13.56MHz pour Mifare Arduino Raspberry Pi device node");
MODULE_AUTHOR("Caproute <cap.route@freemail.bcd>");
MODULE_LICENSE("GPL v2");

// Local definitions
struct cardio_dev {
    struct cdev cdev;
};
static int major;
static struct cardio_dev *cio_dev;

// Init & Exit
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

__init static int cardio_init(void)
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

    //pr_info("cmdlock: %d\n", mfrc->cmd_lock);
    //unsigned int cmd_reg_cmd;
    //regmap_read(rm, MFRC522_CMDREG_CMD, &cmd_reg_cmd);
    //pr_info("cmd reg cmd: %d\n", cmd_reg_cmd);

    u32 version;
    if (of_property_read_u32(device_node, MFRC522_PROP, &version)) {
        pr_err("%s: Did not find property \"%s\"\n", __func__, MFRC522_PROP);
        return 1;
    } else {
        pr_info("%s: \"%s\": %u\n", __func__, MFRC522_PROP, version);
    }

    return 0;
}

static void cardio_destroy(struct cardio_dev *dev)
{
    cdev_del(&dev->cdev);
    kfree(dev);
}

__exit static void cardio_exit(void)
{
    dev_t dev;

    dev = MKDEV(major, 0);
    cardio_destroy(cio_dev);
    unregister_chrdev_region(dev, 1);

    pr_info("Goodbye, GISTRE card !\n");
}

module_init(cardio_init);
module_exit(cardio_exit);
