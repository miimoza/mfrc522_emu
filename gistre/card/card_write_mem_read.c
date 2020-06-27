#include "card_write_funcs.h"

ssize_t mem_read(struct regmap *regmap)
{
    pr_info("%s\n", __func__);
    unsigned int len;

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
    regmap_read(regmap, MFRC522_FIFOLEVELREG_LEVEL, &len);

    pr_info("len: %u\n", len);

    size_t i;
    for (i = 0; i < len && i < 64; i++) {
        pr_info("reading from MFRC522_FIFODATAREG: ");
        regmap_read(regmap, MFRC522_FIFODATAREG, (void *)(&c_dev->buffer[i]));
        pr_info("%d\n", c_dev->buffer[i]);
        c_dev->buffer_len = i;
    }
    c_dev->buffer[i] = '\0';

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
    return len;
}
