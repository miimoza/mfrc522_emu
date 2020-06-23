#idndef CARD_H
#define CARD_H

#include <linux/kernel.h>
#include <linux/module.h>

#include "../mfrc522.h"

#define MFRC522_NAME "mfrc522_emu"
#define MFRC522_PROP MFRC522_PROP_VERSION

struct cardio_dev {
    struct cdev cdev;
};

__init int cardio_init(void);
__exit void cardio_exit(void);

int major;
struct cardio_dev *cio_dev;

#endif
