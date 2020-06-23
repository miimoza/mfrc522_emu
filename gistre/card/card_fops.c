#include "card_fops.h"

struct file_operations cardio_fops = {
    .owner = THIS_MODULE,
    .read = cardio_read,
    .write = cardio_write
    /* Others functions are using the kernel's defaults */
};
