#include "pch.h"
#include "Day4.h"

#include "Common/FileUtils.h"
#include <fmt/core.h>

namespace Day4
{
	void ParseLine(const std::string& line, u32& firstStart, u32& firstEnd, u32& secondStart, u32& secondEnd)
	{
		const std::string first = line.substr(0, line.find(','));
		const std::string second = line.substr(line.find(',') + 1);

		firstStart = std::stoi(first.substr(0, first.find('-')));
		firstEnd = std::stoi(first.substr(first.find('-') + 1));
		secondStart = std::stoi(second.substr(0, second.find('-')));
		secondEnd = std::stoi(second.substr(second.find('-') + 1));
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 4 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day04/input.txt", lines);

		fmt::print("\n-----[ Part 1 ]-----\n");

		u32 containedCount = 0;
		for (const std::string& line : lines)
		{
			u32 firstStart, firstEnd, secondStart, secondEnd;
			ParseLine(line, firstStart, firstEnd, secondStart, secondEnd);

			// Check if one range fully contains the other
			if ((firstStart <= secondStart && firstEnd >= secondEnd) ||
				(secondStart <= firstStart && secondEnd >= firstEnd))
			{
				containedCount++;
			}
		}

		fmt::print("Total nr of sections that are fully contained in another is {}\n", containedCount);


		fmt::print("\n-----[ Part 2 ]-----\n");

		u32 overlapCount = 0;
		for (const std::string& line : lines)
		{
			u32 firstStart, firstEnd, secondStart, secondEnd;
			ParseLine(line, firstStart, firstEnd, secondStart, secondEnd);

			// Check if the ranges overlap
			if ((firstStart <= secondStart && firstEnd >= secondStart) ||
				(secondStart <= firstStart && secondEnd >= firstStart))
			{
				overlapCount++;
			}
		}

		fmt::print("Total nr of sections that are partially or fully overlapping is {}\n", overlapCount);
	}
}
