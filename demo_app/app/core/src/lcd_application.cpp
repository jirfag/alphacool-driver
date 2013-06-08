#include "lcd_application.hpp"
#include "text_pixels_generator.hpp"
#include "commands_processor.hpp"

namespace LcdApp
{
	LcdApplication::LcdApplication() : device_(new Lcd::LcdDevice("/dev/alp0")), commands_processor_(128)
	{
		Lcd::TextPixelsGenerator::Init();
		commands_processor_.run();
	}

	LcdCommand LcdApplication::construct_command(std::shared_ptr<DataProvider> provider, std::shared_ptr<DataVisualizer> visualizer,
			const std::chrono::milliseconds &interval) const
	{
		return LcdCommand(device_, provider, visualizer, interval);
	}

	void LcdApplication::push_command(const LcdCommand &command)
   	{
	   	commands_processor_.push_command(command);
   	}
}
