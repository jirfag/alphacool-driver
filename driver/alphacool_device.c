#include "alphacool_device.h"

int init_alphacool_device(struct alphacool_device **dev_ptr, struct usb_device *usb_dev, struct usb_interface *dev_interface,
                          struct usb_endpoint_descriptor *bulk_endpoint)
{
	struct alphacool_device *dev;
	*dev_ptr = NULL;
	dev = kmalloc(sizeof(struct alphacool_device), GFP_KERNEL);
	CHECK(dev, -ENOMEM, "Can't allocate memory for alphacool_device object");

	dev->interface = dev_interface;
	dev->open_dev_count = 0;
	dev->bulk_endpoint = bulk_endpoint;
	mutex_init(&dev->mutex_lock);

	alphacool_set_minor_num(dev, -1);
	alphacool_set_initialised_state(dev, 0);
	alphacool_set_usb_dev(dev, usb_dev);
	*dev_ptr = dev;
	return 0;
}

void destroy_alphacool_device(struct alphacool_device *dev)
{
	dev->interface = NULL;
	dev->open_dev_count = 0;
	dev->bulk_endpoint = NULL;

	alphacool_set_minor_num(dev, -1);
	alphacool_set_initialised_state(dev, 0);
	alphacool_set_usb_dev(dev, NULL);

	kfree(dev);
}

void alphacool_set_minor_num(struct alphacool_device *dev, int minor_num)
{
	dev->minor_num = minor_num;
}

void alphacool_set_initialised_state(struct alphacool_device *dev, int state)
{
	dev->is_initialised = state;
}

int alphacool_get_initialised_state(const struct alphacool_device *dev)
{
	return dev->is_initialised;
}

struct usb_device *alphacool_get_usb_dev(struct alphacool_device *dev)
{
	return dev->usb_dev;
}

void alphacool_set_usb_dev(struct alphacool_device *dev, struct usb_device *usb_dev)
{
	dev->usb_dev = usb_dev;
}

