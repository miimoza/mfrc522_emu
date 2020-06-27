#include <linux/regmap.h>
#include <string.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card.h"
#include "card_fops.h"



ssize_t card_write(struct file *file, const char __user *buf, size_t len,
                   loff_t *off /* unused */)
{
    pr_info("%s()\n", __func__);

    struct regmap *regmap;
    regmap = mfrc522_get_regmap(dev_to_mfrc522(mfrc522_find_dev()));

    size_t buf_size = strlen(buf);
    if (buf_size >= 10 && strncmp(buf, "mem_write:"))
    {
        size_t buflen_size = 0;
        for (; buf[buflen_size + 10] != '\0' && buf[buflen_size + 10] != ':'; buflen_size++);
        if (i == 0)
            return 0;

        char buflen_str[buflen_size];
        memcpy(buflen_str, &buf[10], buflen_size - 1);
        buflen_str[buflen_size - 1] = '\0';
        size_t buflen = atoi(buflen_str);

        if (buf_size >= 10 + buflen_size + 1 && buf[10 + buflen_size] == ':')
        {
            pr_info("buf:%s, buflen_size:%d, buflen_str:%s, buflen:%d, data:%s\n", buf, buflen_size, buflen_str, buflen, buf + 10 + buflen_size + 1);
            mem_write(regmap, buf + 10 + buflen_size + 1, buflen);
        }
        else
            return 0;
    }
    else if (buf_size == 8 && strncmp(buf, "mem_read"))
    {
        mem_read(regmap);
    }
    else if (buf_size == 11 && strncmp(buf, "gen_rand_id"))
    {
        gen_rand_id(regmap);
    }
    else
    {
        return 0;
    }

    pr_info("MEM\n");


    // MEMWRITE
    regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);
    pr_info("FIFO_FLUSH\n");
    regmap_write(regmap, MFRC522_FIFOLEVELREG_FLUSH, 0x1);

    size_t i;
    for (i = 0; i < len; i++) {
        pr_info("writting in MFRC522_FIFODATAREG: %d\n", 97 + i);
        regmap_write(regmap, MFRC522_FIFODATAREG, 97 + i);
    }
    pr_info("writting in MFRC522_FIFODATAREG: %d\n", 0);
    regmap_write(regmap, MFRC522_FIFODATAREG, 0);

    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);



    // MEMREAD
    regmap_write(regmap, MFRC522_CMDREG, MFRC522_MEM);

    for (i = 0; i < len; i++) {
        pr_info("reading from MFRC522_FIFODATAREG: ");
        regmap_read(regmap, MFRC522_FIFODATAREG, (void *)(&c_dev->buffer[i]));
        pr_info("%d\n", c_dev->buffer[i]);
        c_dev->buffer_len = i;
    }
    c_dev->buffer[i] = '\0';

    pr_info("MFRC522_IDLE\n");
    regmap_write(regmap, MFRC522_CMDREG, MFRC522_IDLE);


    // GENRANDID


    return len;
}
