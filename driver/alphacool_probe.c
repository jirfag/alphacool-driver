#include "alphacool_probe.h"
#include "alphacool_cmd.h"
#include "alphacool_device.h"

/* All fucntions in this file are being executed in the context of the USB hub kernel thread, therefore
	we can sleep in them
*/

static struct usb_endpoint_descriptor *get_bulk_endpoint_descriptor(struct usb_interface *dev_interface)
{
	struct usb_host_interface *cur_interface = dev_interface->cur_altsetting;
	int is_out_endpoint, is_bulk_endpoint;
	struct usb_endpoint_descriptor *endpoint;
	int endpoints_count = cur_interface->desc.bNumEndpoints;
	if (endpoints_count != 1)
		return NULL; // We process only bulk out interface with 1 endpoint

	endpoint = &cur_interface->endpoint[0].desc;
	is_out_endpoint = (endpoint->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT;
	is_bulk_endpoint = (endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK;
	CHECK(is_out_endpoint && is_bulk_endpoint, NULL, "Bad endpoint. Is bulk = %d, is out = %d", is_bulk_endpoint, is_out_endpoint);

	LOG_I("Found good bulk out endpoint");
	return endpoint;
}

static int alphacool_probe_internal(struct usb_interface *dev_interface, const struct usb_device_id *dev_id)
{
	struct usb_device *usb_dev;
	struct usb_endpoint_descriptor *bulk_endpoint;
	struct alphacool_device *alphacool_dev = NULL;
	int init_res;

	LOG_I("Probing of device");
	usb_dev = interface_to_usbdev(dev_interface);
	CHECK(usb_dev, -ENODEV, "Can't get usb_device object from interface");

	bulk_endpoint = get_bulk_endpoint_descriptor(dev_interface);
	CHECK(bulk_endpoint, -ENODEV, "Bad interface: can't find only one bulk out endpoint");
	CHECK(alphacool_cmd_get_resolution(usb_dev) == RES_200x64, -ENODEV,
			"Current resolution of ALPHACOOL LCD is not supported by this driver");

	init_res = init_alphacool_device(&alphacool_dev, usb_dev, dev_interface, bulk_endpoint);
	CHECK(init_res == 0, init_res, "ALPHACOOL driver initialization for current device failed");

	CHECK(usb_register_dev(dev_interface, &alphacool_class) == 0, -ENODEV, "Can't register alphacool device");
	usb_set_intfdata(dev_interface, alphacool_dev);
	mutex_lock(&alphacool_dev->mutex_lock);
	alphacool_set_minor_num(alphacool_dev, dev_interface->minor);
	mutex_unlock(&alphacool_dev->mutex_lock);

	return 0;
}

int alphacool_probe(struct usb_interface *dev_interface, const struct usb_device_id *dev_id)
{
	int res;
	if (mutex_lock_interruptible(&usb_mutex))
		return -EINTR;
	res = alphacool_probe_internal(dev_interface, dev_id);
	mutex_unlock(&usb_mutex);
	return res;
}

void alphacool_disconnect(struct usb_interface *dev_interface)
{
	struct alphacool_device *dev;

	mutex_lock(&usb_mutex);

	dev = usb_get_intfdata(dev_interface);
	LOG_I("DISCONNECT");
	usb_set_intfdata(dev_interface, NULL);
	usb_deregister_dev(dev_interface, &alphacool_class);
	mutex_lock(&dev->mutex_lock);
	if (dev) {
		if (dev->open_dev_count == 0)
			destroy_alphacool_device(dev);
		else
			alphacool_set_usb_dev(dev, NULL);
	}
	mutex_unlock(&dev->mutex_lock);
	mutex_unlock(&usb_mutex);
}

