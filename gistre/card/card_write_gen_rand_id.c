#include "card_write_funcs.h"

void gen_rand_id(struct regmap *regmap)
{
    regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
    //regmap_write(regmap, MFRC522_FIFOLEVELREG_FLUSH, 0x1);

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_GENERATERANDOMID);

    //regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
