#include "pch.h"
#include "StringUtils.h"

namespace Common::StringUtils
{
	// Implementation from https://iq.opengenus.org/split-string-in-cpp/
	std::vector<std::string> Split(const std::string& str, const char& delim)
	{
		std::vector<std::string> output{};

		size_t start = 0;
		size_t end = str.find(delim);

		while (end != std::string::npos)
		{
			output.push_back(str.substr(start, end - start));

			start = end + 1;
			end = str.find(delim, start);
		}

		output.push_back(str.substr(start, end - start));

		return output;
	}
}
