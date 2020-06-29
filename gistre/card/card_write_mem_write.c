#include "card_write_funcs.h"

void mem_write(struct regmap *regmap, const char *buf, size_t len)
{
	regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
	size_t i;
	for (i = 0; i < 25; i++) {
		if (i < len) {
			regmap_write(regmap, MFRC522_FIFODATAREG, buf[i]);
		} else {
			regmap_write(regmap, MFRC522_FIFODATAREG, '\0');
		}
	}
	regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
