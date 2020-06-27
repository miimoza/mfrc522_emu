#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>



MODULE_AUTHOR("Geoffrey Le Gourriérec");
MODULE_DESCRIPTION("A module exporting a printk() function.");
MODULE_LICENSE("GPL v2");



__init
static int my_printk_init(void) {

	/* Do nothing. */
	pr_info("Insertion of my_printk\n");
	return 0;
}

__exit
static void my_printk_exit(void) {

	/* Do nothing. */
	pr_info("Removal of my_printk\n");
}

void my_printk(const char *msg) {

	printk(KERN_INFO "[my_printk] %s\n", msg);
}
EXPORT_SYMBOL_GPL(my_printk);



module_init(my_printk_init);
module_exit(my_printk_exit);
