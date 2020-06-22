#include <linux/kernel.h>
#include <linux/module.h>
#include "mfrc522.h"
#include "mfrc522_emu.h"
#include <linux/regmap.h>

__init
static int gistre_card_init(void) {
	pr_info("Hello, GISTRE card !\n");

	struct device *dev = mfrc522_find_dev();
	struct mfrc522_dev *mfrc = dev_to_mfrc522(dev);
	struct regmap *rm = mfrc522_get_regmap(mfrc);


	pr_info("cmdlock: %d\n", mfrc->cmd_lock);

	unsigned int cmd_reg_cmd;
	regmap_read(rm, MFRC522_CMDREG_CMD, &cmd_reg_cmd);

	pr_info("cmd reg cmd: %d\n", cmd_reg_cmd);

	return 0;
}

__exit
static void gistre_card_exit(void) {

	pr_info("Goodbye, GISTRE card !\n");
}

module_init(gistre_card_init);
module_exit(gistre_card_exit);
