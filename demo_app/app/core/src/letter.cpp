#include "letter.hpp"
#include <assert.h>

namespace Lcd
{
	Letter::Letter(const char *pixels, size_t width, size_t height) : width_(width), height_(height), pixels_(pixels, pixels + width * height)
	{
		assert(width <= MAX_LETTER_WIDTH && height <= MAX_LETTER_HEIGHT);
	}

Letter::Letter() : width_(EMPTY_LETTER_WIDTH), height_(EMPTY_LETTER_HEIGHT), pixels_(EMPTY_LETTER_WIDTH * EMPTY_LETTER_HEIGHT, 0)
	{ }

	const std::vector<char> &Letter::pixels() const { return pixels_; }
	size_t Letter::width() const { return width_; }
	size_t Letter::height() const { return height_; }
}
