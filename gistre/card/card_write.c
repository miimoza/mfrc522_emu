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

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
    regmap_write(regmap, MFRC522_FIFOLEVELREG_FLUSH, 0x1);

    size_t i;
    for (i = 0; i < len; i++) {
        regmap_write(regmap, MFRC522_FIFODATAREG, 97 + i);
    }
    regmap_write(regmap, MFRC522_FIFODATAREG, 0);

    for (i = 0; i < len; i++) {
        regmap_read(regmap, MFRC522_FIFODATAREG, c_dev->buffer[i]);
        c_dev->buffer_len = i;
    }
    c_dev->buffer[i] = '\0';

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);

    return len;
}
