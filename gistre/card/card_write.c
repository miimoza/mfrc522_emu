#include <linux/regmap.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card_fops.h"

ssize_t card_write(struct file *file, const char __user *buf, size_t len,
                   loff_t *off /* unused */)
{
    pr_info("[WRITE]");

    struct device *device;
    struct mfrc522_dev *mfrc522_dev;
    struct regmap *regmap;

    device = mfrc522_find_dev();
    mfrc522_dev = dev_to_mfrc522(device);
    regmap = mfrc522_get_regmap(mfrc522_dev);

    regmap_write(regmap, MFRC522_FIFODATAREG, 0);

    return 0;
}
