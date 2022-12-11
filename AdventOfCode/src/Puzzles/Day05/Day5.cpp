#include "pch.h"
#include "Day5.h"

#include "Common/FileUtils.h"
#include "Common/StringUtils.h"
#include <fmt/core.h>

namespace Day5
{
	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 5 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day05/input.txt", lines);

		fmt::print("\n-----[ Part 1 ]-----\n");
		ContainerStack stack(lines);

		std::vector<Command> commands{};

		// Parse the commands (they start on line 10 of the input file)
		for (u32 ln = 10; ln < lines.size(); ln++)
		{
			const std::string& line = lines[ln];

			std::vector split = Common::StringUtils::Split(line, ' ');

			const u32 amount = std::stoi(split[1]);
			const u32 fromStack = std::stoi(split[3]) - 1;
			const u32 toStack = std::stoi(split[5]) - 1;
			commands.push_back({ amount, fromStack, toStack });
		}

		for (const auto& [amount, fromStack, toStack] : commands)
		{
			stack.Move(amount, fromStack, toStack, false);
		}

		fmt::print("After loading, the stack status is {}\n", stack.GetStatus());


		fmt::print("\n-----[ Part 2 ]-----\n");

		stack.ResetState();

		for (const auto& [amount, fromStack, toStack] : commands)
		{
			stack.Move(amount, fromStack, toStack, true);
		}

		fmt::print("After loading with the CrateMover 9001, the stack status is {}\n", stack.GetStatus());
	}

	ContainerStack::ContainerStack(const std::vector<std::string>& inputLines)
		: m_InputLines(inputLines)
	{
		// Initialize the container stacks with data
		ResetState();
	}

	void ContainerStack::Move(u32 amount, u32 fromStack, u32 toStack, bool keepOrder)
	{
		std::vector<char> temp{};

		// Get the last amount of items from the fromStack, add them to temp, and remove them from fromStack
		for (u32 i = 0; i < amount; ++i)
		{
			temp.push_back(m_Stacks[fromStack].back());
			m_Stacks[fromStack].pop_back();
		}

		if (!keepOrder)
		{
			// Add the temp items to toStack (first out, last in)
			for (char c : temp)
			{
				m_Stacks[toStack].push_back(c);
			}
		}
		else
		{
			// Add the temp items to toStack (last out, first in)
			for (u32 i = temp.size(); i > 0; i--)
			{
				m_Stacks[toStack].push_back(temp[i - 1]);
			}
		}
	}

	void ContainerStack::ResetState()
	{
		for (auto& stack : m_Stacks)
		{
			stack.clear();
		}

		for (u32 ln = 8; ln > 0; --ln)
		{
			const std::string& line = m_InputLines[ln - 1];
			for (u32 stack = 0; stack < m_Stacks.size(); stack++)
			{
				char container = line[stack * 4 + 1];
				if (container != ' ')
				{
					m_Stacks[stack].push_back(container);
				}
			}
		}
	}

	std::string ContainerStack::GetStatus() const
	{
		std::string output;

		for (const auto& stack : m_Stacks)
		{
			if (stack.empty())
			{
				output.push_back(' ');
			}
			else
			{
				output.push_back(stack.back());
			}
		}

		return output;
	}
}
