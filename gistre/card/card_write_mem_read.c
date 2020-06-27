#include "card_write_funcs.h"

ssize_t mem_read(struct regmap *regmap)
{
    unsigned int len;

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);

    //regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
    regmap_read(regmap, MFRC522_FIFOLEVELREG_LEVEL, &len);


    size_t i;
    for (i = 0; i < len && i < 25; i++) {
        regmap_read(regmap, MFRC522_FIFODATAREG, (void *)(&c_dev->buffer[i]));
        c_dev->buffer_len = i;
        if (c_dev->buffer[i] == '\0')
            break;
    }

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);

    return len;
}
