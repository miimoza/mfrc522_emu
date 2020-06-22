#ifndef GISTRE_CARD_FOPS_H
#define GISTRE_CARD_FOPS_H

#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/regmap.h>
#include <linux/of.h>

struct file_operations cardio_fops;

ssize_t cardio_read(struct file *file, const char __user *buf,
    size_t len, loff_t *off /* unused */);

ssize_t cardio_write(struct file *file, const char __user *buf,
    size_t len, loff_t *off /* unused */);

#endif /* GISTRE_CARD_FOPS_H */
