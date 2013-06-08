#ifndef _SIMPLE_DATA_PROVIDER_
#define _SIMPLE_DATA_PROVIDER_

#include "data_provider.hpp"

namespace LcdApp
{
	class SimpleDataProvider : public DataProvider
	{
	private:
		const std::string data_;
	public:
		SimpleDataProvider(const std::string &data);
		virtual const std::string get_data();
	};
}

#endif

