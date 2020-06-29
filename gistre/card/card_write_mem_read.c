#include "card_write_funcs.h"

void mem_read(struct regmap *regmap)
{
	size_t i;
	regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);

	if (c_dev->debug)
		printk("<RD>\n");

	for (i = 0; i < 25; i++) {
		regmap_read(regmap, MFRC522_FIFODATAREG,
			    (void *)(&c_dev->buffer[i]));
		if (c_dev->debug) {
			printk(KERN_CONT "%02x", c_dev->buffer[i]);
			if ((i + 1) % 5 == 0)
				printk("\n");
			else
				printk(KERN_CONT " ");
		}
	}

	c_dev->buffer_len = i;
	regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);
}
