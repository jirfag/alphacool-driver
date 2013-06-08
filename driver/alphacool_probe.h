#ifndef ALPHACOOL_PROBE_H
#define ALPHACOOL_PROBE_H

#include "alphacool_global.h"

int alphacool_probe(struct usb_interface *dev_interface, const struct usb_device_id *dev_id);

void alphacool_disconnect(struct usb_interface *dev_interface);

#endif

