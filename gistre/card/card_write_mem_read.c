#include "card_write_funcs.h"

ssize_t mem_read(struct regmap *regmap)
{
    pr_info("%s\n", __func__);
    unsigned int len;

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
    regmap_read(regmap, MFRC522_FIFOLEVELREG_LEVEL, &len);

    len &= 0xFE;
    len = len >> 1;

    pr_info("len: %u\n", len);

    size_t i;
    for (i = 0; i < len && i < 25; i++) {
        pr_info("reading from MFRC522_FIFODATAREG: ");
        regmap_read(regmap, MFRC522_FIFODATAREG, (void *)(&c_dev->buffer[i]));
        pr_info("%d\n", c_dev->buffer[i]);
        c_dev->buffer_len = i;
        if (c_dev->buffer[i] == '\0')
            break;
    }
    pr_info("In c_dev->buffer_len:%d\n", c_dev->buffer_len);
    pr_info("Store %s in c_dev->buffer\n", c_dev->buffer);

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
    return len;
}
