#ifndef _CURRENT_TIME_DATA_PROVIDER_
#define _CURRENT_TIME_DATA_PROVIDER_

#include "data_provider.hpp"

namespace LcdApp
{
	class CurrentTimeDataProvider : public DataProvider
	{
	public:
		virtual const std::string get_data();
	};
}

#endif

