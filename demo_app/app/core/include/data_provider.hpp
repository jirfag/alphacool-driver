#ifndef _DATA_PROVIDER_HPP_
#define _DATA_PROVIDER_HPP_

#include <string>

namespace LcdApp
{
	class DataProvider
	{
	public:
		virtual const std::string get_data() = 0;
		virtual ~DataProvider() { }
	};
}

#endif

