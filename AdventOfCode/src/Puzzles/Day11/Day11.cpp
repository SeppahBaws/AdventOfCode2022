#include "pch.h"
#include "Day11.h"

#include <functional>
#include <fmt/core.h>
#include "Common/FileUtils.h"
#include "Common/StringUtils.h"

namespace Day11
{
	void SimulateMonkey(Monkey& monkey, std::vector<Monkey>& allMonkeys, std::function<u64(u64)> modifier)
	{
		// Skip over the monkey if it doesn't have any items
		if (monkey.startingItems.empty())
			return;

		for (u64 item : monkey.startingItems)
		{
			u64 worryLevel = item;
			switch (monkey.operation)
			{
			case '*':
				worryLevel *= monkey.operationValue.value_or(worryLevel);
				break;
			case '+':
				worryLevel += monkey.operationValue.value_or(worryLevel);
				break;
			default: break;
			}

			worryLevel = modifier(worryLevel);

			if (worryLevel % monkey.divisibleBy == 0)
			{
				allMonkeys[monkey.throwToWhenTrue].startingItems.push_back(worryLevel);
			}
			else
			{
				allMonkeys[monkey.throwToWhenFalse].startingItems.push_back(worryLevel);
			}

			monkey.nrOfItemsInspected++;
		}

		monkey.startingItems.clear();
	}

	void PrintMonkeyBusiness(const std::vector<Monkey>& monkeys)
	{
		u32 idx = 0;
		for (const Monkey& monkey : monkeys)
		{
			fmt::print("Monkey {} inspected items {} times.\n", idx, monkey.nrOfItemsInspected);
			idx++;
		}
	}

	void ParseMonkeys(const std::vector<std::string>& lines, std::vector<Monkey>& monkeys)
	{
		monkeys = {};

		// Advance i by 2, to skip over the blank line in between
		for (u32 i = 0; i < lines.size() - 5; i += 2)
		{
			Monkey& monkey = monkeys.emplace_back();

			// Parse starting items
			{
				i++;
				std::vector items = Common::StringUtils::Split(Common::StringUtils::RemoveCharacters(lines[i].substr(18), " "), ',');

				monkey.startingItems = {};

				for (const std::string& item : items)
				{
					monkey.startingItems.push_back(std::stoi(item));
				}
			}

			// Parse operation
			{
				i++;
				std::vector items = Common::StringUtils::Split(lines[i], ' ');

				if (items.back() == "old")
				{
					monkey.operationValue = std::nullopt;
				}
				else
				{
					monkey.operationValue = std::stoi(items.back());
				}

				monkey.operation = items[items.size() - 2][0];
			}

			// Parse divisible test
			{
				i++;
				std::vector items = Common::StringUtils::Split(lines[i], ' ');
				monkey.divisibleBy = std::stoi(items.back());
			}

			// Parse monkeys to pass to
			{
				// Monkey to pass to when true
				i++;
				std::vector items = Common::StringUtils::Split(lines[i], ' ');
				monkey.throwToWhenTrue = std::stoi(items.back());

				// Monkey to pass to when false
				i++;
				items = Common::StringUtils::Split(lines[i], ' ');
				monkey.throwToWhenFalse = std::stoi(items.back());
			}
		}
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 11 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day11/input.txt", lines);

		std::vector<Monkey> monkeys{};

		ParseMonkeys(lines, monkeys);


		fmt::print("\n-----[ Part 1 ]-----\n");

		{
			// Simulate 20 rounds
			for (u32 round = 0; round < 20; round++)
			{
				for (Monkey& monkey : monkeys)
				{
					SimulateMonkey(monkey, monkeys, [](u64 item)
					{
						return item / 3;
					});
				}
			}

			PrintMonkeyBusiness(monkeys);

			std::ranges::sort(monkeys, [](const Monkey& left, const Monkey& right)
			{
				return left.nrOfItemsInspected > right.nrOfItemsInspected;
			});

			fmt::print("The level of monkey business is {}\n", monkeys[0].nrOfItemsInspected * monkeys[1].nrOfItemsInspected);
		}

		fmt::print("\n-----[ Part 2 ]-----\n");

		// Props to this guy for the solution, because what the actual fuck
		// https://github.com/python-b5/advent-of-code-2022/blob/main/day_11.cpp

		ParseMonkeys(lines, monkeys);

		{
			u64 product = 1;

			for (const Monkey& monkey : monkeys)
			{
				product *= monkey.divisibleBy;
			}


			// Simulate 10000 rounds
			for (u32 round = 1; round <= 10000; round++)
			{
				for (Monkey& monkey : monkeys)
				{
					SimulateMonkey(monkey, monkeys, [product](u64 item)
					{
						return item % product;
					});
				}

				if (round == 1 || round == 20 || round % 1000 == 0)
				{
					fmt::print("\n== After round {} ==\n", round);
					PrintMonkeyBusiness(monkeys);
				}
			}

			std::ranges::sort(monkeys, [](const Monkey& left, const Monkey& right)
			{
				return left.nrOfItemsInspected > right.nrOfItemsInspected;
			});

			u64 monkeyBusiness = monkeys[0].nrOfItemsInspected * monkeys[1].nrOfItemsInspected;
			fmt::print("The level of monkey business is {}\n", monkeyBusiness);
		}
	}
}
