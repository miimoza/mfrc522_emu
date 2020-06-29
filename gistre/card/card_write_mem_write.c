#include "card_write_funcs.h"

void mem_write(struct regmap *regmap, const char *buf, size_t len)
{
	size_t i;
	char c;
	regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);

	if (c_dev->debug)
		printk("<WR>\n");

	for (i = 0; i < 25; i++) {
		if (i < len)
			c = buf[i];
		else
			c = '\0';

		regmap_write(regmap, MFRC522_FIFODATAREG, c);

		if (c_dev->debug) {
			printk(KERN_CONT "%02x", c);
			if ((i + 1) % 5 == 0)
				printk("\n");
			else
				printk(KERN_CONT " ");
		}
	}

	regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
