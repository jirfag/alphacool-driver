#include "alphacool_global.h"
#include "alphacool_probe.h"
#include "alphacool_fops.h"

#define USB_ALPHACOOL_MINOR_BASE 0
#define USB_ALPHACOOL_VENDOR_ID 0x60C
#define USB_ALPHACOOL_PRODUCT_ID 0x4EB

DEFINE_MUTEX(usb_mutex);

static struct usb_device_id alphacool_table [] = {
	{ USB_DEVICE(USB_ALPHACOOL_VENDOR_ID, USB_ALPHACOOL_PRODUCT_ID) },
	{ }
};

MODULE_DEVICE_TABLE (usb, alphacool_table);

static struct file_operations alphacool_fops = {
	.owner = THIS_MODULE,
	.write = alphacool_fops_write,
	.open = alphacool_fops_open,
	.release = alphacool_fops_release
};

struct usb_class_driver alphacool_class = {
	.name = "alp%d",
	.fops = &alphacool_fops,
	.minor_base = USB_ALPHACOOL_MINOR_BASE
};

struct usb_driver alphacool_driver = {
	.name        = "ALPHACOOL USB LCD driver",
	.id_table    = alphacool_table,
	.probe       = alphacool_probe,
	.disconnect  = alphacool_disconnect
};

static int __init usb_alphacool_init(void)
{
	int result = usb_register(&alphacool_driver);
	if (result < 0) {
		LOG_E("usb_register failed for the driver. Error number %d", result);
		return -1;
	}
	LOG_I("Alphacool initiated");
	return 0;
}

static void __exit usb_alphacool_exit(void)
{
	LOG_I("Exit");
	usb_deregister(&alphacool_driver);
}

module_exit(usb_alphacool_exit);
module_init(usb_alphacool_init);

MODULE_AUTHOR("Denis Isaev");
MODULE_LICENSE("GPL");

