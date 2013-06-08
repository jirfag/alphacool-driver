#include "std_data_visualizer.hpp"
#include "lcd_string.hpp"
#include "text_pixels_generator.hpp"

namespace LcdApp
{
	StdDataVisualizer::StdDataVisualizer() : begin_point_(0, 2), font_height_(5), font_type_(Lcd::LFT_NORMAL)
		{ }

	StdDataVisualizer::StdDataVisualizer(const Lcd::Point &begin_point, size_t font_height, Lcd::LcdFontType font_type) :
		begin_point_(begin_point), font_height_(font_height), font_type_(font_type)
	{ }

	PixelsData StdDataVisualizer::visualize(const std::string &data) const
	{
		Lcd::LcdString lcd_str(data, begin_point_, font_height_, font_type_);
		return Lcd::TextPixelsGenerator::generate_pixels(lcd_str);
	}
}
