#include <linux/regmap.h>

#include "../mfrc522.h"
#include "../mfrc522_dev.h"
#include "card_fops.h"

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
