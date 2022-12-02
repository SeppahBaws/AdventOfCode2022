#pragma once

namespace Common
{
	bool ReadFileSync(const std::string& path, std::string& outputBuf);
	bool ReadFileSync(const std::string& path, std::vector<std::string>& output);
}
