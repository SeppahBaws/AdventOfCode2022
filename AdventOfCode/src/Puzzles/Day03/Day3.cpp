#include "pch.h"
#include "Day3.h"

#include <unordered_map>
#include <fmt/core.h>
#include "Common/FileUtils.h"
#include "Common/Timer.h"

namespace Day3
{
	u32 GetPriority(char c)
	{
		if (c >= 'a' && c <= 'z')
		{
			return 1 + c - 'a';
		}
		if (c >= 'A' && c <= 'Z')
		{
			return 27 + (c - 'A');
		}

		return 0;
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 2 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day03/input.txt", lines);

		fmt::print("\n-----[ Part 1 ]-----\n");

		Common::Timer timer;

		u32 total = 0;
		for (const std::string& line : lines)
		{
			// loop through chars in left
			// check if char appears in right
			// if it does, we need to calculate that character's priority, and add it to the sum.

			const std::string left = line.substr(0, line.length() / 2);
			const std::string right = line.substr(line.length() / 2);

			for (const char& c : left)
			{
				if (right.find(c) != std::string::npos)
				{
					total += GetPriority(c);
					break;
				}
			}
		}

		fmt::print("The total is {}\n", total);
		fmt::print("Total time took {}ns\n", timer.PollNs());


		fmt::print("\n-----[ Part 2 ]-----\n");

		timer.Reset();
		total = 0;
		for (u32 i = 0; i < lines.size() - 2; i += 3)
		{
			for (const char& c : lines[i])
			{
				if (lines[i + 1].find(c) != std::string::npos && lines[i + 2].find(c) != std::string::npos)
				{
					total += GetPriority(c);
					break;
				}
			}
		}
		fmt::print("The total is {}\n", total);
		fmt::print("Total time took {}ns\n", timer.PollNs());
	}
}
