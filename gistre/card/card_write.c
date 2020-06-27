#include <linux/regmap.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

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
            break;
        }
        result = (10 * result) + digit;
    }

    return result;
}



static void mem_write_parser(struct regmap *regmap, char *buf, size_t len)
{
    size_t buflen_size = 0;
    for (; buf[buflen_size + 10] != '\0' && buf[buflen_size + 10] != ':'; buflen_size++);
    if (buflen_size == 0)
    {
        pr_err("Buffer len Size Null\n");
        return;
    }

    char buflen_str[buflen_size + 1];
    strncpy(buflen_str, &buf[10], buflen_size);
    buflen_str[buflen_size] = '\0';

    ssize_t buflen = atoi(buflen_str);
    if (buflen == -1)
    {
        pr_err("Buffer Len not a digit\n");
        return ;
    }

    if (len >= 10 + buflen_size + 1 && buf[10 + buflen_size] == ':')
        mem_write(regmap, buf + 10 + buflen_size + 1, buflen);
    else
        pr_err("Command Parsing Error\n");

}


ssize_t card_write(struct file *file, const char __user *buf, size_t len,
                   loff_t *off /* unused */)
{
    struct regmap *regmap;
    regmap = mfrc522_get_regmap(dev_to_mfrc522(mfrc522_find_dev()));

    char *cmd = kmalloc(len + 1, GFP_KERNEL);
    copy_from_user(cmd, buf, len);
    cmd[len] = '\0';

    if (len >= 12 && !strncmp(cmd, "mem_write:", 10))
        mem_write_parser(regmap, cmd, len);
    else if (len == 8 && !strncmp(cmd, "mem_read", 8))
        len = mem_read(regmap);
    else if (len == 11 && !strncmp(cmd, "gen_rand_id", 11))
        gen_rand_id(regmap);
    else
        pr_err("Unknown Command\n");

    kfree(cmd);

    return len;
}
