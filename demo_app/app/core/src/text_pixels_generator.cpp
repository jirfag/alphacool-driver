#include "text_pixels_generator.hpp"

#include "fonts/font8.hpp"
#include "fonts/font16.hpp"
#include "fonts/font24.hpp"
#include "fonts/font24_bold.hpp"
#include "fonts/font24_italic.hpp"
#include "fonts/font32.hpp"
#include "fonts/font40.hpp"
#include "fonts/font48.hpp"
#include "fonts/font56.hpp"
#include "fonts/font64.hpp"

#include <iostream>
#include <assert.h>

namespace Lcd {
	TextPixelsGenerator::FontsGroup TextPixelsGenerator::letters;

	static const Point LCD_SIZE(200, 8);

	static inline bool go_to_next_line(Point &screen_position, size_t line_height)
	{
		if (screen_position.y() + line_height * 2 > LCD_SIZE.y()) {
			return false;
		}

		screen_position.set_y(screen_position.y() + line_height);
		screen_position.set_x(0);

		return true;
	}

	const Letter &TextPixelsGenerator::get_letter(size_t font_height, LcdFontType font_type, char letter)
	{
		assert(font_type > LFT_MIN && font_type < LFT_COUNT && font_height <= letters[font_type].size());
		return letters[font_type][font_height - 1][letter];
	}

	std::shared_ptr<const PixelsRect> TextPixelsGenerator::generate_pixels(const LcdString &text)
	{
		auto text_pixels = std::shared_ptr<PixelsRect>(new PixelsRect(LCD_SIZE));
		Point screen_position(text.begin_point());
		const size_t font_height = text.font_height();
		const std::string &str = text.str();
		for (auto it = str.cbegin(); it != str.cend(); ++it) {
			const uint8_t current_char = static_cast<uint8_t>(*it);
			if (current_char == '\n') {
				if (!go_to_next_line(screen_position, font_height))
					return text_pixels;
				continue;
			}
			const Letter &letter = get_letter(font_height, text.font_type(), current_char);
			if (screen_position.x() + letter.width() > LCD_SIZE.x()) {
				if (!go_to_next_line(screen_position, font_height))
					return text_pixels;
			}
			text_pixels->copy_letter_to_rect(screen_position, letter);
			screen_position += Point(letter.width(), 0);
		}

		return text_pixels;
	}

	static void init_fonts_height_group(TextPixelsGenerator::FontsHeightGroup &letters, const std::vector<const uint8_t *> &raw_fonts, const std::vector<size_t> &raw_font_widths)
	{
		assert(raw_fonts.size() == raw_font_widths.size());
		letters.reserve(raw_fonts.size());
		for (size_t i = 0; i < raw_fonts.size(); ++i) {
			const size_t font_height = i + 1;
			const size_t font_width = raw_font_widths[i];
			const size_t letter_size = font_width * font_height;
			const char *pixels = reinterpret_cast<const char *>(raw_fonts[i]);
			TextPixelsGenerator::FontLetters current_letters;
			current_letters.reserve(256);
			for (size_t j = 0; j < 256; ++j)
				current_letters.push_back(Letter(pixels + letter_size * j, font_width, font_height));
			letters.push_back(current_letters);
		}
	}

	void TextPixelsGenerator::Init()
	{
		letters.resize(LFT_COUNT);
		const std::vector<const uint8_t *> fonts = { lucida8, lucida16, lucida24, lucida32, lucida40, lucida48, lucida56, lucida64 };
		const std::vector<size_t> font_widths    = { 5, 10, 14, lucida32_width, lucida40_width, lucida48_width, lucida56_width, lucida64_width };
		init_fonts_height_group(letters[LFT_NORMAL], fonts, font_widths);
		
		const std::vector<const uint8_t *> bold_fonts = { lucida8, lucida16, lucida24_bold, lucida32, lucida40, lucida48, lucida56, lucida64 };
		const std::vector<size_t> bold_font_widths    = { 5, 10, 15, lucida32_width, lucida40_width, lucida48_width, lucida56_width, lucida64_width };
		init_fonts_height_group(letters[LFT_BOLD], bold_fonts, bold_font_widths);

		const std::vector<const uint8_t *> italic_fonts = { lucida8, lucida16, lucida24_italic, lucida32, lucida40, lucida48, lucida56, lucida64 };
		const std::vector<size_t> italic_font_widths    = { 5, 10, 14, lucida32_width, lucida40_width, lucida48_width, lucida56_width, lucida64_width };
		init_fonts_height_group(letters[LFT_ITALIC], italic_fonts, italic_font_widths);
	}
}

