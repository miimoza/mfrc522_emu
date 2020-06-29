#include "card_write_funcs.h"

void mem_read(struct regmap *regmap)
{
	regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);

	size_t i;
	for (i = 0; i < 25; i++)
		regmap_read(regmap, MFRC522_FIFODATAREG,
			    (void *)(&c_dev->buffer[i]));
	c_dev->buffer_len = i;

	regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
