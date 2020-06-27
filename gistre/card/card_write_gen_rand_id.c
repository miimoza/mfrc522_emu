#include "card_write_funcs.h"

void gen_rand_id(struct regmap *regmap)
{
    pr_info("%s\n", __func__);
    regmap_write(regmap, MFRC522_CMDREG, MFRC522_GENERATERANDOMID);
    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
