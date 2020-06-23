#ifndef CARD_FOPS_H
#define CARD_FOPS_H

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

extern struct file_operations card_fops;

ssize_t card_read(struct file *file, char __user *buf, size_t len,
                  loff_t *off /* unused */);

ssize_t card_write(struct file *file, const char __user *buf, size_t len,
                   loff_t *off /* unused */);

#endif /* CARD_FOPS_H */
