#ifndef _DATA_VISUALIZER_HPP_
#define _DATA_VISUALIZER_HPP_

#include <memory>
#include "pixels_rect.hpp"

namespace LcdApp
{
	typedef std::shared_ptr<const Lcd::PixelsRect> PixelsData;

	class DataVisualizer
	{
	public:
		virtual PixelsData visualize(const std::string &data) const = 0;
		virtual ~DataVisualizer() { }
	};
}

#endif

