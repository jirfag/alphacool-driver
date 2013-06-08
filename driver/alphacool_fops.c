#include "alphacool_fops.h"
#include "alphacool_device.h"
#include "alphacool_cmd.h"

int alphacool_fops_open(struct inode *inode, struct file *file)
{
	int init_res = 0;
	struct alphacool_device *dev;
	int dev_minor_num;
	struct usb_interface *dev_interface;

	if (mutex_lock_interruptible(&usb_mutex))
		return -ERESTARTSYS;

	dev_minor_num = iminor(inode);
	dev_interface = usb_find_interface(&alphacool_driver, dev_minor_num);
	mutex_unlock(&usb_mutex);

	CHECK(dev_interface, -ENODEV, "Can't find alphacool device with minor number %d", dev_minor_num);

	dev = usb_get_intfdata(dev_interface);
	CHECK(dev, -ENODEV, "Can't extract alphacool_device object from interface");


	if (mutex_lock_interruptible(&dev->mutex_lock))
		return -ERESTARTSYS;

	if (!alphacool_get_initialised_state(dev)) {
		init_res = alphacool_cmd_init_device(alphacool_get_usb_dev(dev));
		alphacool_set_initialised_state(dev, init_res == 0 ? 1 : 0);
	} else {
		LOG_I("Device already initialised");
	}
	if (!init_res)
		++dev->open_dev_count;
	mutex_unlock(&dev->mutex_lock);
	CHECK(!init_res, -EFAULT, "Can't init device");

	file->private_data = dev;

	LOG_I("Device opened");
	return 0;
}

int alphacool_fops_release(struct inode *inode, struct file *file)
{
	struct alphacool_device *dev = file->private_data;
	CHECK(dev, -ENODEV, "Can't extract alphacool_device object from file");

	if (mutex_lock_interruptible(&dev->mutex_lock))
		return -ERESTARTSYS;
	if (dev->open_dev_count == 0) {
		mutex_unlock(&dev->mutex_lock);
		LOG_E("Device is not opened");
		return -ENODEV;
	}
	if (--dev->open_dev_count == 0) {
		if (alphacool_get_usb_dev(dev)) {
			alphacool_cmd_deinit_device(alphacool_get_usb_dev(dev));
			alphacool_set_initialised_state(dev, 0);
		}
		else { // device was unplugged before closing file
			mutex_unlock(&dev->mutex_lock);
			destroy_alphacool_device(dev);
			LOG_E("Device was closed after disconnecting");
			return 0;
		}
	}
	mutex_unlock(&(dev->mutex_lock));
	LOG_I("Device closed");
	return 0;
}

ssize_t alphacool_fops_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
	/*
		Function 'write' draws and fill a rectangle in ALPHACOOL LCD 200x64.
		Input data format([something] means tht omething is 1 byte size):
		[begin.x][begin.y][width][height][entire_pixels]
		Therefore, size of input data at least 5 bytes. X and Y begin form zero; begin - left-upper corner of rect.
		width and height > 0 and < LCD size. entire pixels in special format.
		Bad input data is being ingored (for example, if width or height == 0).
	*/
{
	struct alphacool_device *dev = file->private_data;
	unsigned int begin_x, begin_y, width, height;
#define INPUT_PARAMS_LEN 4
	char input_params[INPUT_PARAMS_LEN];
	const char *pixels = NULL;
	size_t pixels_size = 0;

	CHECK(count >= 5, -EFAULT, "Bad input (%u bytes): should be at least 5 bytes input data", (unsigned int)count);
	CHECK(!copy_from_user(input_params, user_buf, sizeof(input_params)), -EFAULT, "Can't copy user data");

	CHECK(dev, -ENODEV, "Can't extract alphacool_device object from file");

	begin_x = (__u8)input_params[0];
	begin_y = (__u8)input_params[1];
	width = (__u8)input_params[2];
	height = (__u8)input_params[3];

	CHECK(begin_x + width <= ALPHACOOL_LCD_WIDTH && begin_y + height <= ALPHACOOL_LCD_HEIGHT / 8, -EFAULT, "Bad input params: "
			"begin.x = %u, begin.y = %u, width = %u, height = %u", begin_x, begin_y, width, height);
	pixels_size = width * height;
	CHECK(pixels_size + INPUT_PARAMS_LEN == count, -EFAULT, "Bad input pixels array");

	pixels = (const char *)kmalloc(pixels_size, GFP_KERNEL);
	CHECK(pixels, -EFAULT, "Can't allocate pixels array of size %u", (unsigned int)pixels_size);
	CHECK(!copy_from_user((void *)pixels, user_buf + INPUT_PARAMS_LEN, pixels_size), -EFAULT, "Can't copy pixels form userland");
#undef INPUT_PARAMS_LEN

	if (mutex_lock_interruptible(&dev->mutex_lock)) {
		kfree((void *)pixels);
		return -ERESTARTSYS;
	}
	alphacool_cmd_draw_rect(alphacool_get_usb_dev(dev), dev->bulk_endpoint->bEndpointAddress, (__u8)begin_x,
		(__u8)begin_y, (__u8)width, (__u8)height, pixels);
	mutex_unlock(&dev->mutex_lock);
	kfree((void *)pixels);
	return count;
}
