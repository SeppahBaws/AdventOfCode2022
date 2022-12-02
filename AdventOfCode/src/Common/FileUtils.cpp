#include "pch.h"
#include "FileUtils.h"

#include <fmt/core.h>

namespace Common
{
	bool ReadFileSync(const std::string& path, std::string& outputBuf)
	{
		std::ifstream file(path, std::ios::binary | std::ios::in | std::ios::beg);
		if (!file)
		{
			fmt::print("Failed to read file '{}'", path);
			return false;
		}

		outputBuf.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
		file.close();

		return true;
	}

	bool ReadFileSync(const std::string& path, std::vector<std::string>& output)
	{
		std::ifstream file(path, std::ios::binary | std::ios::in | std::ios::beg);
		if (!file)
		{
			fmt::print("Failed to read file '{}'", path);
			return false;
		}

		output.resize(0);

		std::string line;
		while (std::getline(file, line))
		{
			output.emplace_back(line);
		}

		file.close();
		return true;
	}
}
