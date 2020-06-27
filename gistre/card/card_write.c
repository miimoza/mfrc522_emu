#include <linux/regmap.h>
#include <linux/string.h>

#include "../mfrc522.h"
#include "../mfrc522_emu.h"
#include "card_write_funcs.h"
#include "card.h"
#include "card_fops.h"

static ssize_t atoi(char *string)
{
    int result = 0;
    unsigned int digit;

    for (;; string += 1) {
        digit = *string - '0';
        if (digit > 9) {
            return -1;
        }
        result = (10 * result) + digit;
    }

    return result;
}

static void mem_write_parser(struct regmap *regmap, char *buf, size_t len)
{
    pr_info("%s()\n", __func__);

    size_t buflen_size = 0;
    for (; buf[buflen_size + 10] != '\0' && buf[buflen_size + 10] != ':'; buflen_size++);
    if (buflen_size == 0)
        return 0;

    char buflen_str[buflen_size];
    memcpy(buflen_str, &buf[10], buflen_size - 1);
    buflen_str[buflen_size - 1] = '\0';
    size_t buflen = atoi(buflen_str);
    if (buflen == -1)
        return 0;


    if (len >= 10 + buflen_size + 1 && buf[10 + buflen_size] == ':')
    {
        pr_info("buf:%s, buflen_size:%d, buflen_str:%s, buflen:%d, data:%s\n", buf, buflen_size, buflen_str, buflen, buf + 10 + buflen_size + 1);
        mem_write(regmap, buf + 10 + buflen_size + 1, buflen);
    }
}


ssize_t card_write(struct file *file, const char __user *buf, size_t len,
                   loff_t *off /* unused */)
{
    pr_info("%s()\n", __func__);

    struct regmap *regmap;
    regmap = mfrc522_get_regmap(dev_to_mfrc522(mfrc522_find_dev()));


    if (len >= 11 && strncmp(buf, "mem_write:", 10) == 0)
        mem_write_parser(regmap, buf, len);
    else if (len == 9 && strncmp(buf, "mem_read", 8) == 0)
        mem_read(regmap);
    else if (len == 12 && strncmp(buf, "gen_rand_id", 11) == 0)
        gen_rand_id(regmap);
    else
        pr_info("ca match po lau\n");

    return len;
}
