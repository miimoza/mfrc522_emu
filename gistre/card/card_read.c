#include <linux/regmap.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card_fops.h"

ssize_t card_read(struct file *file, char __user *buf, size_t len,
                    loff_t *off /* unused */)
{
    pr_info("[READ]\n");

    struct device *device;
    struct mfrc522_dev *mfrc522_dev;
    struct regmap *regmap;

    device = mfrc522_find_dev();
    mfrc522_dev = dev_to_mfrc522(device);
    regmap = mfrc522_get_regmap(mfrc522_dev);

    unsigned int reg = 0;
    unsigned int *val;

    regmap_read(regmap, reg, val);


    pr_info("val: %s\n", val);

    return 0;
}
