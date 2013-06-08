#include "pixels_rect.hpp"
#include <assert.h>

namespace Lcd {

	PixelsRect::PixelsRect(const Point &size) : pixels_(size.square(), 0), size_(size)
	{
		assert(size.square());
	}

	void PixelsRect::copy_letter_to_rect(const Point &begin_point, const Letter &letter)
	{
		const size_t letter_width = letter.width(), letter_height = letter.height();
		assert(begin_point.x() + letter_width <= size_.x() && begin_point.y() + letter_height <= size_.y());
		const size_t shift = begin_point.y() * size_.x() + begin_point.x();

		for (size_t i = 0; i < letter_width; ++i)
			for (size_t j = 0; j < letter_height; ++j)
				pixels_[shift + i + (letter_height - j - 1) * size_.x()] = letter.pixels()[i * letter_height + j];
	}

	const std::vector<char> &PixelsRect::pixels() const
	{
		return pixels_;
	}

	const Point &PixelsRect::size() const
	{
		return size_;
	}

	size_t PixelsRect::width() const
	{
		return size_.x();
	}

	size_t PixelsRect::height() const
	{
		return size_.y();
	}

	size_t PixelsRect::square() const
	{
		return size_.square();
	}
}
