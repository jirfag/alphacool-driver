#ifndef TEXT_PIXELS_GENERATOR_HPP
#define TEXT_PIXELS_GENERATOR_HPP

#include <array>
#include <memory>
#include "point.hpp"
#include "letter.hpp"
#include "pixels_rect.hpp"
#include "lcd_string.hpp"

namespace Lcd {

	class TextPixelsGenerator {
	public:
		//TODO: use Boost::logger and Boost::singletone
		typedef std::vector<Letter> FontLetters;
		typedef std::vector<FontLetters> FontsHeightGroup;
		typedef std::vector<FontsHeightGroup> FontsGroup;
		static void Init();
		static std::shared_ptr<const PixelsRect> generate_pixels(const LcdString &text);
	private:
		static FontsGroup letters;
		static const Letter &get_letter(size_t font_height, LcdFontType font_type, char letter);
	};

}

#endif

