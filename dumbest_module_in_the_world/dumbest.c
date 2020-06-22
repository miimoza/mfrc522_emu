#include <linux/kernel.h>
#include <linux/module.h>

__init
static int dumb_init(void) {

	pr_info("Hello, World!\n");
	return 0;
}

__exit
static void dumb_exit(void) {

	pr_info("Goodbye, World!\n");
}

module_init(dumb_init);
module_exit(dumb_exit);
