#ifndef _LCD_STRING_HPP_
#define _LCD_STRING_HPP_

#include <string>
#include "point.hpp"

namespace Lcd
{
	enum LcdFontType
	{
		LFT_MIN    = -1,
		LFT_NORMAL = 0,
		LFT_BOLD   = 1,
		LFT_ITALIC = 2,
		LFT_COUNT  = 3
	};

	class LcdString
	{
	private:
		std::string str_;
		Point begin_;
		size_t font_height_;
		LcdFontType font_type_;
	public:
		LcdString(const std::string &str, const Point &begin, size_t font_height, LcdFontType font_type);

		const std::string &str() const;
		const Point &begin_point() const;
		size_t font_height() const;
		LcdFontType font_type() const;
	};
}

#endif

