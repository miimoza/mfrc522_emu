#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL v2");

static int   nb_greetings;
module_param(nb_greetings, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(nb_greetings, "Number of times to greet.");

static char *name;
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "Who to greet.");

static void greet(void) {

        int i;
	for (i = 0; i < nb_greetings; ++i) {

		pr_info("Hello, %s!\n", name);
	}
}

static void bye(void) {

        int i;
	for (i = 0; i < nb_greetings; ++i) {

		pr_info("Goodbye, %s.\n", name);
	}
}

__init
static int my_init(void) {

	greet();
	return 0;
}

__exit
static void my_exit(void) {

	bye();
}

module_init(my_init);
module_exit(my_exit);
