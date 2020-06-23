#include "gistre_card_fops.h"

struct file_operations cardio_fops = {
    .owner = THIS_MODULE,
    .read = cardio_read,
    .write = cardio_write
    /* Others functions are using the kernel's defaults */
};

ssize_t cardio_read(struct file *file, char __user *buf, size_t len,
                    loff_t *off /* unused */)
{
    struct device *device;
    struct mfrc522_dev *mfrc522_dev;
    struct regmap *regmap;

    device = mfrc522_find_dev();
    mfrc522_dev = dev_to_mfrc522(device);
    regmap = mfrc522_get_regmap(mfrc522_dev);
    //regmap_read(struct regmap *map, unsigned int reg, unsigned int *val);
    return 0;
}

ssize_t cardio_write(struct file *file, const char __user *buf, size_t len,
                     loff_t *off /* unused */)
{
    struct device *device;
    struct mfrc522_dev *mfrc522_dev;
    struct regmap *regmap;

    device = mfrc522_find_dev();
    mfrc522_dev = dev_to_mfrc522(device);
    regmap = mfrc522_get_regmap(mfrc522_dev);
    //regmap_write(struct regmap *map, unsigned int reg, unsigned int val);
    return 0;
}
