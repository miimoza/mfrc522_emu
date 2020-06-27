#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("Geoffrey Le Gourriérec");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple \"Hello world\" module.");

__init
static int base_init(void) {

	pr_info("Hello, World! (init)\n");
	return 0;
}

__exit
static void base_exit(void) {

	pr_info("Hello, World! (exit)\n");
}

module_init(base_init);
module_exit(base_exit);
