#include "current_time_data_provider.hpp"
#include <ctime>
#include <time.h>

namespace LcdApp
{
	const std::string CurrentTimeDataProvider::get_data()
	{
		char time_buf[128];
		time_t now;
		time(&now);
		strftime(time_buf, sizeof(time_buf), "%H:%M:%S", gmtime(&now));

		return std::string(time_buf);
	}
}
