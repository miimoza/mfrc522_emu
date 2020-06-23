#include <linux/regmap.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card_fops.h"

ssize_t card_read(struct file *file, char __user *buf, size_t len,
                    loff_t *off /* unused */)
{
    pr_info("[READ]\n");

    struct mfrc522_dev *mfrc522_dev = dev_to_mfrc522(mfrc522_find_dev());
    struct regmap *regmap = mfrc522_get_regmap(mfrc522_dev);

    /*
    To read out data from a specific register address in the MFRC522,
    the host controller must use the following procedure:
    
    •Firstly, a write access to the specific register address must be performed as indicated in the frame that follows
    •The first byte of a frame indicates the device address according to the I2C-bus rules
    •The second byte indicates the register address. No data bytes are added
    •The Read/Write bit is 0

    After the write access, read access can start. The host sends the device address of the MFRC522.
    In response, the MFRC522 sends the content of the read access register.
    In one frame all data bytes can be read from the same register address.
    This enables fast FIFO buffer access or register polling.The Read/Write (R/W) bit is set to logic 1
    */



    unsigned int data;
	regmap_read(regmap, MFRC522_FIFODATAREG, &data);
	pr_info("Data: %s\n", data);

    return 0;
}
