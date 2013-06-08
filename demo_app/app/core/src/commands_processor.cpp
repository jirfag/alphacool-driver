#include "commands_processor.hpp"

namespace LcdApp
{
	CommandsProcessor::CommandsProcessor(size_t commands_queue_capacity) : commands_queue_(commands_queue_capacity),
		need_stop_thread_(false)
	{ }

	void CommandsProcessor::push_command(const LcdCommand &command)
	{
		commands_queue_.push(command);
	}

	void CommandsProcessor::run()
	{
		if (thread_.joinable())
			return;
		thread_ = std::thread(&CommandsProcessor::do_events_loop, this);
	}

	void CommandsProcessor::do_events_loop()
	{
		const std::chrono::milliseconds std_interval(1000);
		while (!need_stop_thread_.load()) {
			const std::chrono::milliseconds &cur_interval = current_command_.interval();
			const bool timeouted = !commands_queue_.pop(cur_interval == std::chrono::milliseconds::zero() ? std_interval : cur_interval, current_command_);
			const bool command_is_repetative = cur_interval != std::chrono::milliseconds::zero();
			if (!current_command_ || (timeouted && !command_is_repetative))
				continue;
			current_command_();
		}
	}

	CommandsProcessor::~CommandsProcessor()
	{
		need_stop_thread_.store(true);
		thread_.join();
	}
}
