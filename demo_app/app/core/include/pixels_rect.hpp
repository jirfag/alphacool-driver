#ifndef PIXELS_RECT_HPP
#define PIXELS_RECT_HPP

#include <vector>
#include <iterator>
#include "point.hpp"
#include "letter.hpp"

namespace Lcd {

	class PixelsRect {
	private:
		std::vector<char> pixels_;
		Point size_;
	public:
		PixelsRect(const Point &size);

		void copy_letter_to_rect(const Point &begin_point, const Letter &letter);
		const std::vector<char> &pixels() const;
		size_t width() const;
		size_t height() const;
		size_t square() const;
		const Point &size() const;
	};
}
#endif

