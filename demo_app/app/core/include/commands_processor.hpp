#ifndef _COMMANDS_PROCESSOR_HPP_
#define _COMMANDS_PROCESSOR_HPP_

#include <thread>
#include <atomic>
#include "lcd_command.hpp"
#include "timeouted_buffer.hpp"

namespace LcdApp
{
	class CommandsProcessor
	{
	private:
		LcdCommand current_command_;
		TimeoutedBuffer<LcdCommand> commands_queue_;
		std::thread thread_;
		std::atomic_bool need_stop_thread_;

		void do_events_loop();
	public:
		CommandsProcessor(size_t commands_queue_capacity);
		void push_command(const LcdCommand &command);
		void run();
		~CommandsProcessor();
	};
}

#endif

