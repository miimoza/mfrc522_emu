#include "card_fops.h"

struct file_operations card_fops = {
    .owner = THIS_MODULE,
    .read = card_read,
    .write = card_write
    /* Others functions are using the kernel's defaults */
};
