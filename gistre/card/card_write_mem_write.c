#include "card_write_funcs.h"

void mem_write(struct regmap *regmap, const char __user *buf, size_t len)
{
	regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);

	size_t i;
	for (i = 0; i < len; i++)
		regmap_write(regmap, MFRC522_FIFODATAREG, buf[i]);

	regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
