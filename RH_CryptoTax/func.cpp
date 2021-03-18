#include "func.h"

namespace Func
{
	bool checkInt(const std::string &str, int &num)
	{
		try {
			num = std::stoi(str);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	bool checkUInt(const std::string &str, unsigned int &num)
	{
		try {
			num = std::stoi(str);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	bool checkDouble(const std::string &str, double &num)
	{
		try {
			num = std::stod(str);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	bool checkUShort(const std::string &str, unsigned short &num)
	{
		try {
			num = std::stoi(str);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	bool delimFinder(const std::string& str, const char &delim, std::vector<unsigned int>& positions)
	{
		positions.clear();
		for (auto iterator_at = std::find(str.begin(), str.end(), delim), end_at = str.end();
			iterator_at != end_at;
			iterator_at = std::find(iterator_at + 1, end_at, delim)
			)
		{
			positions.push_back(std::distance(str.begin(), iterator_at));
		}

		return (positions.empty() == false);
	}
}