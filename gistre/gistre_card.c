#include <linux/kernel.h>
#include <linux/module.h>

__init
static int gistre_card_init(void) {
	pr_info("Hello, GISTRE card !\n");
	return 0;
}

__exit
static void gistre_card_exit(void) {

	pr_info("Goodbye, GISTRE card !\n");
}

module_init(gistre_card_init);
module_exit(gistre_card_exit);
