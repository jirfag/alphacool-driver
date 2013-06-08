#include "lcd_command.hpp"

namespace LcdApp
{
	LcdCommand::LcdCommand(std::shared_ptr<Lcd::LcdDevice> device, std::shared_ptr<DataProvider> provider, std::shared_ptr<DataVisualizer> visualizer,
		const std::chrono::milliseconds &interval) : device_(device), data_provider_(provider), data_visualizer_(visualizer), interval_(interval)
	{ }

	LcdCommand::LcdCommand() : interval_(std::chrono::milliseconds::zero())
   	{ }

	void LcdCommand::operator()()
	{
		if (!(*this)) return;

		auto pixels = data_visualizer_->visualize(data_provider_->get_data());
		device_->write_all_pixels(*pixels);
	}

	LcdCommand::operator bool() const
	{
		return device_ && data_provider_ && data_visualizer_;
	}

	const std::chrono::milliseconds &LcdCommand::interval() const
   	{
	   	return interval_;
   	}
}
