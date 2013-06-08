#ifndef ALPHACOOL_DEVICE_H
#define ALPHACOOL_DEVICE_H

#include "alphacool_global.h"

struct alphacool_device {
	struct usb_device *usb_dev;
	struct usb_interface *interface;
	unsigned int minor_num;
	unsigned int open_dev_count;
	struct mutex mutex_lock;
	struct usb_endpoint_descriptor *bulk_endpoint;
	int is_initialised;
};

int init_alphacool_device(struct alphacool_device **dev_ptr, struct usb_device *usb_dev, struct usb_interface *dev_interface,
                          struct usb_endpoint_descriptor *bulk_endpoint);

void destroy_alphacool_device(struct alphacool_device *dev);

void alphacool_set_minor_num(struct alphacool_device *dev, int minor_num);
void alphacool_set_initialised_state(struct alphacool_device *dev, int state);
int alphacool_get_initialised_state(const struct alphacool_device *dev);
void alphacool_set_usb_dev(struct alphacool_device *dev, struct usb_device *usb_dev);
struct usb_device *alphacool_get_usb_dev(struct alphacool_device *dev);

#endif

