#ifndef _LCD_COMMAND_HPP_
#define _LCD_COMMAND_HPP_

#include <chrono>
#include <memory>
#include "data_provider.hpp"
#include "data_visualizer.hpp"
#include "lcd_device.hpp"


namespace LcdApp
{
	class LcdApplication;

	class LcdCommand
	{
	private:
		std::shared_ptr<Lcd::LcdDevice> device_;
		std::shared_ptr<DataProvider> data_provider_;
		std::shared_ptr<DataVisualizer> data_visualizer_;
		std::chrono::milliseconds interval_;

		LcdCommand(std::shared_ptr<Lcd::LcdDevice> device, std::shared_ptr<DataProvider> provider, std::shared_ptr<DataVisualizer> visualizer,
			const std::chrono::milliseconds &interval);
	public:
		LcdCommand();

		void operator()();
		operator bool() const;

		const std::chrono::milliseconds &interval() const;
		
		friend class LcdApplication;
	};
}

#endif

