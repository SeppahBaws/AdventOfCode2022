#pragma once

namespace Common::StringUtils
{
	std::vector<std::string> Split(const std::string& str, const char& delim);

	// Removes all characters from `str` that exist in the `lookup` string.
	std::string RemoveCharacters(const std::string& str, const std::string& lookup = " ");
}
