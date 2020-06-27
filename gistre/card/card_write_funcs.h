#include <linux/regmap.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card.h"
#include "card_fops.h"

ssize_t mem_read(struct regmap *regmap);
void mem_write(struct regmap *regmap, const char __user *buf, size_t len);
void gen_rand_id(struct regmap *regmap);
