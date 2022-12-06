#include "pch.h"
#include "Day6.h"

#include <fmt/core.h>
#include "Common/FileUtils.h"

namespace Day6
{
	bool HasDuplicates(const std::string& window, u32 maxWidth, size_t& lastIdx)
	{
		for (u32 i = 1; i < maxWidth; i++)
		{
			const size_t idx = window.substr(0, i).find_last_of(window[i]);
			if (idx != std::string::npos)
			{
				lastIdx = idx;
				return true;
			}
		}

		return false;
	}

	size_t FindStartOfMsgMarker(const std::string& sequence, u32 nrUniqueChars)
	{
		size_t start = 0;
		
		while (start < sequence.size() - nrUniqueChars)
		{
			std::string window = sequence.substr(start, nrUniqueChars);
			size_t lastDuplicatedIndex;
			if (HasDuplicates(window, nrUniqueChars, lastDuplicatedIndex))
			{
				start += lastDuplicatedIndex + 1;
			}
			else
			{
				return start + nrUniqueChars;
			}
		}

		return std::string::npos;
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 2 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day06/input.txt", lines);

		fmt::print("\n-----[ Part 1 ]-----\n");

		const std::string& sequence = lines[0];

		fmt::print("The result is {}\n", FindStartOfMsgMarker(sequence, 4));

		fmt::print("\n-----[ Part 2 ]-----\n");

		fmt::print("The result is {}\n", FindStartOfMsgMarker(sequence, 14));
	}
}
