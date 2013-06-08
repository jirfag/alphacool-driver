#include "simple_data_provider.hpp"

namespace LcdApp
{
	SimpleDataProvider::SimpleDataProvider(const std::string &data) : data_(data) { }

	const std::string SimpleDataProvider::get_data() { return data_; }
}
