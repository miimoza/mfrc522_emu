#ifndef CARD_H
#define CARD_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>


#include "../mfrc522.h"

#define MFRC522_NAME "mfrc522_emu"
#define MFRC522_PROP MFRC522_PROP_VERSION


// Metadata
MODULE_DESCRIPTION("CARD DRIVER MRFC522: RFID RC522, Module MFRC-522 RF IC RFID S50 13.56MHz");
MODULE_AUTHOR("Dorian Vinai <dorian.vinai@epita.fr>, Antoine Coulon <antoine.coulon@epita.fr>");
MODULE_LICENSE("GPL v2");

struct card_dev {
    struct cdev cdev;
};


extern const int major;
extern const struct card_dev *cio_dev;


__init int card_init(void);
__exit void card_exit(void);


module_init(card_init);
module_exit(card_exit);

#endif
