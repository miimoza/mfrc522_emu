#include <linux/kernel.h>
#include <linux/module.h>

/* Imported from my_printk module. */
void my_printk(const char *msg);



MODULE_AUTHOR("Geoffrey Le Gourriérec");
MODULE_DESCRIPTION("A module that consumes my_printk().");
MODULE_LICENSE("GPL v2");



__init
static int printk_consumer_init(void) {

	my_printk("Hello, World! (init)");
	return 0;
}

__exit
static void printk_consumer_exit(void) {
	my_printk("Hello, World! (exit)");
}

module_init(printk_consumer_init);
module_exit(printk_consumer_exit);
