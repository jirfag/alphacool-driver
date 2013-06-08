#ifndef ALPHACOOL_FOPS_H
#define ALPHACOOL_FOPS_H

#include "alphacool_global.h"

int alphacool_fops_open(struct inode *inode, struct file *file);

int alphacool_fops_release(struct inode *inode, struct file *file);

ssize_t alphacool_fops_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos);

#endif

