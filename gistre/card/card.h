#ifndef CARD_H
#define CARD_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>


#include "../mfrc522.h"

#define MFRC522_NAME "mfrc522_emu"
#define MFRC522_PROP MFRC522_PROP_VERSION

struct card_dev {
    struct cdev cdev;
};

__init int card_init(void);
__exit void card_exit(void);

int major;
struct card_dev *cio_dev;

#endif
