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
            return mem_write(regmap, buf + 10 + buflen_size + 1, buflen);
        }
        else
            return 0;
    }
    else if (buf_size == 8 && strncmp(buf, "mem_read"))
    {
        return mem_read(regmap);
    }
    else if (buf_size == 11 && strncmp(buf, "gen_rand_id"))
    {
        return gen_rand_id(regmap);
    }

    return 0;
}
