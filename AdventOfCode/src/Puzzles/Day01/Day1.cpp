#include "pch.h"
#include "Day1.h"

#include <fmt/core.h>

#include "Common/FileUtils.h"

namespace Day1
{
	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 1 ]=====\n");


		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day01/input.txt", lines);


		// Calculate the amount of times that the depth increases.
		fmt::print("\n-----[ Part 1 ]-----\n");

		// Initialize with one elf to kick-start the algorithm
		std::vector<i32> caloriesPerElf{ 0 };

		for (const std::string& line : lines)
		{
			if (line.empty())
			{
				caloriesPerElf.push_back(0);
				continue;
			}

			caloriesPerElf.back() += std::stoi(line);
		}

		std::ranges::sort(caloriesPerElf);
		fmt::print("The #1 elf is carrying in total: {}\n", caloriesPerElf.back());

		// Calculate in groups.
		fmt::print("\n-----[ Part 2 ]-----\n");

		i32 topThreeTotal = 0;
		for (int i = 0; i < 3; i++)
		{
			topThreeTotal += *(caloriesPerElf.end() - 1 - i);
		}

		fmt::print("The top three elves are carrying in total: {}\n", topThreeTotal);
	}
}
