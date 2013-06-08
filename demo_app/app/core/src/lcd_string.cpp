#include "lcd_string.hpp"

namespace Lcd
{
	LcdString::LcdString(const std::string &str, const Point &begin, size_t font_height, LcdFontType font_type) :
			str_(str), begin_(begin), font_height_(font_height), font_type_(font_type)
		{ }

	const std::string &LcdString::str() const { return str_; }
	const Point &LcdString::begin_point() const { return begin_; }
	size_t LcdString::font_height() const { return font_height_; }
	LcdFontType LcdString::font_type() const { return font_type_; }
}
