#include "alphacool_cmd.h"

#define RQ_TYPE_USB_RECV 0xC0
#define RQ_TYPE_USB_SEND 0x40

#define USB_CNTRL_TIMEOUT 5000000 // milliseconds
#define ALPHACOOL_LCD_200x64_RES 0
#define ALPHACOOL_LCD_240x128_RES 1

#define SEND_CMD(dev, req, value, index) \
	usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), (__u8)req, (__u8)RQ_TYPE_USB_SEND, (__u16)value, (__u16)index, \
		(void *)NULL, (__u16)0, (int)msecs_to_jiffies(USB_CNTRL_TIMEOUT))

#define RECV_CMD(dev, req, value, index, length, in_data) \
	usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), (__u8)req, (__u8)RQ_TYPE_USB_RECV, (__u16)value, (__u16)index, \
		(void *)in_data, (__u16)length, (int)msecs_to_jiffies(USB_CNTRL_TIMEOUT))

#define SEND_BULK_DATA(dev, endpoint, data, data_size, transfered_bytes_ptr) \
	usb_bulk_msg(dev, usb_sndbulkpipe(dev, endpoint), data, data_size, transfered_bytes_ptr, (int)msecs_to_jiffies(USB_CNTRL_TIMEOUT))

lcd_resolution_t alphacool_cmd_get_resolution(struct usb_device *usb_dev)
{
	char in_data;
	int received = RECV_CMD(usb_dev, CMD_LCD_GET_RESOLUTION, 0, 0, 1, &in_data);
	CHECK(received == 1, RES_ERROR, "Can't get resolution from device");

	switch (in_data) {
	case (char)ALPHACOOL_LCD_200x64_RES:
		return RES_200x64;
	case (char)ALPHACOOL_LCD_240x128_RES:
		LOG_E("Unsopported resolution");
		return RES_240x128;
	default:
		LOG_E("Unknown resolution");
		return RES_ANOTHER;
	}
}

int alphacool_cmd_init_device(struct usb_device *usb_dev)
{
	LOG_I("preinit res:%d", SEND_CMD(usb_dev, CMD_LCD_INIT, 0, 0)); // first init is necessary and may return error
	CHECK(!SEND_CMD(usb_dev, CMD_LCD_INIT, 0, 0), -ENODEV, "Can't init");
	CHECK(!SEND_CMD(usb_dev, CMD_LCD_CLEAR_SCREEN, 0, 0), -ENODEV, "Can't clear screen");
	CHECK(!SEND_CMD(usb_dev, CMD_LCD_BACKLIGHTS_CONTROL, 1, 0), -ENODEV, "Can't turn on backlighting");

	return 0;
}

int alphacool_cmd_deinit_device(struct usb_device *usb_dev)
{
	CHECK(!SEND_CMD(usb_dev, CMD_LCD_BACKLIGHTS_CONTROL, 0, 0), -ENODEV, "Can't turn off backlighting part1");
	CHECK(!SEND_CMD(usb_dev, CMD_LCD_BACKLIGHTS_CONTROL, 0, 0), -ENODEV, "Can't turn off backlighting part2");
	CHECK(!SEND_CMD(usb_dev, CMD_LCD_CLEAR_SCREEN, 0, 0), -ENODEV, "Can't clear screen");

	return 0;
}

int alphacool_cmd_draw_rect(struct usb_device *usb_dev, unsigned int bulk_endpoint, __u8 begin_x, __u8 begin_y, __u8 width, __u8 height, const char *pixels)
{
	int transfered_bytes = 0;
	__u16 value = begin_x | (begin_y << 8);
	__u16 index = width | (height << 8);
	CHECK(!SEND_CMD(usb_dev, CMD_LCD_WRITE_BEGIN, value, index), -EFAULT, "Can't init writing of rectangle");
	if (SEND_BULK_DATA(usb_dev, bulk_endpoint, (void *)pixels, width * height, &transfered_bytes)) {
		LOG_E("Can't send bulk data in rect writing: %d bytes sent", transfered_bytes);
	}

	CHECK(!SEND_CMD(usb_dev, CMD_LCD_WRITE_END, 0, 0), -EFAULT, "Can't finish writing of rectangle");

	LOG_I("Wrote rect (x0:%u, y0:%u, w:%u, h:%u)", (unsigned int)begin_x, (unsigned int)begin_y, (unsigned int)width, (unsigned int)height);
	return 0;
}
