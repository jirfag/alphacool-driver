#ifndef _STD_DATA_VISUALIZER_HPP_
#define _STD_DATA_VISUALIZER_HPP_

#include "data_visualizer.hpp"
#include "lcd_string.hpp"

namespace LcdApp
{
	class StdDataVisualizer : public DataVisualizer
	{
	private:
		const Lcd::Point begin_point_;
		const size_t font_height_;
		const Lcd::LcdFontType font_type_;
	public:
		StdDataVisualizer();

		StdDataVisualizer(const Lcd::Point &begin_point, size_t font_height, Lcd::LcdFontType font_type);

		virtual PixelsData visualize(const std::string &data) const;
	};
}

#endif

