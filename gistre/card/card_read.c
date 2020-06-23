#include <linux/regmap.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card_fops.h"

ssize_t card_read(struct file *file, char __user *buf, size_t len,
                    loff_t *off /* unused */)
{
    pr_info("[READ]\n");

    struct mfrc522_dev *mfrc522_dev = dev_to_mfrc522(mfrc522_find_dev());
    struct regmap *regmap = mfrc522_get_regmap(mfrc522_dev);

    unsigned int data;
	regmap_read(regmap, MFRC522_FIFODATAREG, &data);
	pr_info("Data: %s\n", data);

    return 0;
}
