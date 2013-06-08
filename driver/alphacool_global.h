#ifndef ALPHACOOL_GLOBAL_H
#define ALPHACOOL_GLOBAL_H

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/types.h> // for atomic_t
#include <linux/slab.h> /* kmalloc() */
#include <linux/usb.h> /* USB stuff */
#include <linux/mutex.h> /* mutexes */
#include <linux/ioctl.h>
#include <asm/uaccess.h> /* copy_*_user */

extern struct usb_driver alphacool_driver;
extern struct usb_class_driver alphacool_class;
extern struct mutex usb_mutex;

#define log_kernel_with_level(log_level, log_name, fmt, args...) \
	printk(log_level "[ALPHACOOL_USB_LCD %s] in %s:%d: "fmt"\n", \
		log_name, __FILE__, __LINE__, ##args)

// log information
#define LOG_I(fmt, args...) log_kernel_with_level(KERN_ALERT, "INFO", fmt, ##args)

// log warning
#define LOG_W(fmt, args...) log_kernel_with_level(KERN_ALERT, "WARN", fmt, ##args)

// log error
#define LOG_E(fmt, args...) log_kernel_with_level(KERN_ALERT, "ERROR", fmt, ##args)

#define CHECK(expr, ret_val, descr, args...) do { if (!(expr)) { LOG_E(descr, ##args); return ret_val; } } while (0)


#endif

