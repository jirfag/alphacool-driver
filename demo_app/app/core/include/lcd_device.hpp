#ifndef LCD_DEVICE_HPP
#define LCD_DEVICE_HPP

#include <string>
#include "point.hpp"
#include "pixels_rect.hpp"

namespace Lcd {

	class LcdDevice {
	private:
		int dev_fd;
		static const int LCD_WIDTH = 200;
		static const int LCD_HEIGHT = 8;
		ssize_t write_pixels(const Point &begin, const PixelsRect &rect) const;
	public:
		LcdDevice(const std::string &dev_name);
		~LcdDevice();
		ssize_t write_all_pixels(const PixelsRect &rect) const;
		bool is_opened() const;
	};
}

#endif

