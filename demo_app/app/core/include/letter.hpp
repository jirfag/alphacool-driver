#ifndef _LETTER_HPP_
#define _LETTER_HPP_

#include <vector>
#include <stddef.h>

namespace Lcd {

	class Letter {
	private:
		static const size_t MAX_LETTER_WIDTH = 40;
		static const size_t MAX_LETTER_HEIGHT = 8;
		static const size_t EMPTY_LETTER_WIDTH = 5;
		static const size_t EMPTY_LETTER_HEIGHT = 1;
		size_t width_, height_;
		std::vector<char> pixels_;
	public:
		Letter(const char *pixels, size_t width, size_t height);
		Letter();

		const std::vector<char> &pixels() const;
		size_t width() const;
		size_t height() const;
	};
}
#endif

