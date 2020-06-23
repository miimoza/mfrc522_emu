#ifndef CARD_FOPS_H
#define CARD_FOPS_H

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

struct file_operations cardio_fops;

ssize_t cardio_read(struct file *file, char __user *buf, size_t len,
                    loff_t *off /* unused */);

ssize_t cardio_write(struct file *file, const char __user *buf, size_t len,
                     loff_t *off /* unused */);

#endif /* CARD_FOPS_H */