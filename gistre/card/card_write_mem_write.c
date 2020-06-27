#include "card_write_funcs.h"

void mem_write(struct regmap *regmap, const char __user *buf, size_t len)
{
    pr_info("%s\n", __func__);
    regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
    regmap_write(regmap, MFRC522_FIFOLEVELREG_FLUSH, 0x1);

    size_t i;
    for (i = 0; i < len; i++) {
        pr_info("writting in MFRC522_FIFODATAREG: %d\n", buf[i]);
        regmap_write(regmap, MFRC522_FIFODATAREG, buf[i]);
    }
    //pr_info("writting in MFRC522_FIFODATAREG: %d\n", 0);
    //regmap_write(regmap, MFRC522_FIFODATAREG, 0);

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
