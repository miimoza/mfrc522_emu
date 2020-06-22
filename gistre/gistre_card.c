#include <linux/kernel.h>
#include <linux/module.h>
#include "mfrc522.h"
#include "mfrc522_emu.h"
#include <linux/regmap.h>
#include <linux/of.h>

#define MFRC522_NAME "mfrc522_emu"

/*
 * Metadata
 */

MODULE_DESCRIPTION("A driver for the dummy \"Mfrc522\" device node");
MODULE_AUTHOR("Caproute <cap.route@gmail.com>");
MODULE_LICENSE("GPL v2");

__init
static int gistre_card_init(void) {
	pr_info("Hello, GISTRE card !\n");

	struct device *device;
	struct mfrc522_dev *mfrc522_dev;
	struct regmap *regmap;
	struct device_node *device_node;

	device = mfrc522_find_dev();
	mfrc522_dev = dev_to_mfrc522(device);
	regmap = mfrc522_get_regmap(mfrc522_dev);
	device_node = of_find_node_by_name(of_root, MFRC522_NAME);
	if (!device_node)
        pr_err("%s: Did not find node %s...\n", __func__, MFRC522_NAME);

	//pr_info("cmdlock: %d\n", mfrc->cmd_lock);

	//unsigned int cmd_reg_cmd;
	//regmap_read(rm, MFRC522_CMDREG_CMD, &cmd_reg_cmd);
	//pr_info("cmd reg cmd: %d\n", cmd_reg_cmd);

	char *version;
	if (of_property_read_string(device_node, MFRC522_PROP_VERSION, &version))
		pr_err("%s: Did not find property \"%s\"\n", __func__, MFRC522_PROP_VERSION);
	else
		pr_info("%s: \"%s\": %s\n", __func__, MFRC522_PROP_VERSION, version);

	return 0;
}

__exit
static void gistre_card_exit(void) {
	pr_info("Goodbye, GISTRE card !\n");
}

module_init(gistre_card_init);
module_exit(gistre_card_exit);
