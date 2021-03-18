#pragma once

#include <vector>
#include <string>


namespace Func
{
	bool checkInt(const std::string &str, int &num);
	bool checkUInt(const std::string &str, unsigned int &num);
	bool checkDouble(const std::string &str, double &num);
	bool checkUShort(const std::string &str, unsigned short &num);
	bool delimFinder(const std::string& str, const char &delim, std::vector<unsigned int>& positions);
}