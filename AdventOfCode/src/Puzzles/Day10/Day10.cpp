#include "pch.h"
#include "Day10.h"

#include <fmt/core.h>
#include "Common/FileUtils.h"
#include "Common/StringUtils.h"

namespace Day10
{
	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 6 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day10/input.txt", lines);

		fmt::print("\n-----[ Part 1 ]-----\n");

		Computer computer{};

		for (const std::string& line : lines)
		{
			std::vector parts = Common::StringUtils::Split(line, ' ');

			// Assume noop
			if (parts.size() == 1)
			{
				computer.DoNoop();
			}
			// Assume addx
			else if (parts.size() == 2)
			{
				computer.DoAddx(std::stoi(parts[1]));
			}
		}

		fmt::print("The total of part 1 is {}\n", computer.GetPart1Total());

		fmt::print("\n-----[ Part 2 ]-----\n");

		computer.PrintScreen();
	}

	Computer::Computer()
		: m_Register(1)
		, m_Cycle()
		, m_Screen({})
	{
	}

	void Computer::Reset()
	{
		m_Cycle = 0;
		m_Register = 1;
	}

	void Computer::DoNoop()
	{
		m_Cycle++;
		EvaluateCycle();
	}

	void Computer::DoAddx(i32 amount)
	{
		m_Cycle++;
		EvaluateCycle();

		m_Cycle++;
		EvaluateCycle();
		m_Register += amount;
	}

	void Computer::PrintScreen() const
	{
		for (const auto& row : m_Screen)
		{
			for (const char c : row)
			{
				fmt::print("{}", c);
			}
			fmt::print("\n");
		}
	}

	void Computer::EvaluateCycle()
	{
		// Part 1 code
		if (m_Cycle < 20 && (m_Cycle - 20) % 40 == 0)
		{
			m_Part1Total += m_Register * m_Cycle;
		}


		// Part 2 code
		const u32 row = (m_Cycle - 1) / 40;
		const u32 col = (m_Cycle - 1) % 40;

		// If m_Cycle is in range of the sprite position (register value), then we write '#' to the screen.
		if (std::abs(static_cast<i32>(col) - m_Register) <= 1)
		{
			m_Screen[row][col] = '#';
		}
		else
		{
			m_Screen[row][col] = '.';
		}
	}
}
