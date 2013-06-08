#include "lcd_device.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <array>
#include <iterator>
#include <iostream>

namespace Lcd
{
	LcdDevice::LcdDevice(const std::string &dev_name)
	{
		dev_fd = open(dev_name.c_str(), O_WRONLY);
	}

	LcdDevice::~LcdDevice()
	{
		if (is_opened())
			close(dev_fd);
	}

	bool LcdDevice::is_opened() const
	{
		return dev_fd != -1;
	}

	ssize_t LcdDevice::write_all_pixels(const PixelsRect &rect) const
	{
		return write_pixels(Point(0, 0), rect);
	}

	ssize_t LcdDevice::write_pixels(const Point &begin, const PixelsRect &rect) const
	{
		assert(begin.x() + rect.width() <= LCD_WIDTH && begin.y() + rect.height() <= LCD_HEIGHT);

		if (!is_opened())
			return -1;

		std::array<char, LCD_WIDTH * LCD_HEIGHT + 4> write_buf;
		write_buf[0] = static_cast<uint8_t>(begin.x());
		write_buf[1] = static_cast<uint8_t>(begin.y());
		write_buf[2] = static_cast<uint8_t>(rect.width());
		write_buf[3] = static_cast<uint8_t>(rect.height());
		assert(rect.square() <= write_buf.size());
		auto it = write_buf.begin();
		std::advance(it, 4);
		std::copy(rect.pixels().cbegin(), rect.pixels().cend(), it);

		assert(dev_fd >= 0);
		return write(dev_fd, write_buf.data(), rect.square() + 4);
	}
}

