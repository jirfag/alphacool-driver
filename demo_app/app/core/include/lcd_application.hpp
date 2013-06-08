#ifndef _LCD_APPLICATION_HPP_
#define _LCD_APPLICATION_HPP_

#include <memory>
#include "lcd_command.hpp"
#include "lcd_device.hpp"
#include "commands_processor.hpp"

namespace LcdApp
{
	class CommandsProcessor;

	class LcdApplication
	{
	private:
		std::shared_ptr<Lcd::LcdDevice> device_;
		CommandsProcessor commands_processor_;
	public:
		LcdApplication();

		LcdCommand construct_command(std::shared_ptr<DataProvider> provider, std::shared_ptr<DataVisualizer> visualizer,
			   	const std::chrono::milliseconds &interval = std::chrono::milliseconds::zero()) const;

		void push_command(const LcdCommand &command);
	};
}

#endif

