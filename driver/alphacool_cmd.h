#ifndef ALPHACOOL_CMD_H
#define ALPHACOOL_CMD_H

#include "alphacool_global.h"

#define CMD_LCD_GET_RESOLUTION 71
#define CMD_LCD_INIT 49
#define CMD_LCD_CLEAR_SCREEN 58
#define CMD_LCD_BACKLIGHTS_CONTROL 67

#define CMD_LCD_WRITE_BEGIN 50
#define CMD_LCD_WRITE_END 51

#define ALPHACOOL_LCD_WIDTH 200
#define ALPHACOOL_LCD_HEIGHT 64

typedef enum lcd_resolution_e {
	RES_200x64,
	RES_240x128,
	RES_ANOTHER,
	RES_ERROR
} lcd_resolution_t;

lcd_resolution_t alphacool_cmd_get_resolution(struct usb_device *usb_dev);

int alphacool_cmd_init_device(struct usb_device *usb_dev);
int alphacool_cmd_deinit_device(struct usb_device *usb_dev);

int alphacool_cmd_draw_rect(struct usb_device *usb_dev, unsigned int bulk_endpoint, __u8 begin_x, __u8 begin_y, __u8 width, __u8 height, const char *pixels);

#endif

