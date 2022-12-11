#include "pch.h"
#include "Day9.h"

#include "Common/FileUtils.h"
#include <fmt/core.h>

#include "Common/StringUtils.h"

namespace Day9
{
	Direction GetDirection(const std::string& input)
	{
		if (input == "L") return Direction::Left;
		if (input == "R") return Direction::Right;
		if (input == "U") return Direction::Up;
		if (input == "D") return Direction::Down;

		throw std::runtime_error("Invalid input!");
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 9 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day09/input.txt", lines);

		// Coordinates system:
		// ^ y
		// |
		// +---> x


		fmt::print("\n-----[ Part 1 ]-----\n");

		Rope smallRope{ 1 };

		for (const std::string& line : lines)
		{
			const std::vector parts = Common::StringUtils::Split(line, ' ');
			const Direction direction = GetDirection(parts[0]);
			const u32 amount = std::stoi(parts[1]);
			// fmt::print("{}\n", line);

			smallRope.SimulateMovement(direction, amount);
		}

		fmt::print("The tail visited {} unique spots\n", smallRope.GetVisitedSpots().size());


		fmt::print("\n-----[ Part 2 ]-----\n");

		Rope bigRope{ 9 };

		for (const std::string& line : lines)
		{
			const std::vector parts = Common::StringUtils::Split(line, ' ');
			const Direction direction = GetDirection(parts[0]);
			const u32 amount = std::stoi(parts[1]);
			// fmt::print("{}\n", line);
		
			bigRope.SimulateMovement(direction, amount);
		}

		fmt::print("The tail visited {} unique spots\n", bigRope.GetVisitedSpots().size());
	}

	void Rope::SimulateMovement(Direction direction, u32 amount)
	{
		switch (direction)
		{
		case Direction::Left:
			for (u32 x = 0; x < amount; x++)
			{
				m_Knots[0].x -= 1;
				for (u32 i = 1; i < m_Knots.size(); i++)
				{
					MoveKnot(m_Knots[i - 1], m_Knots[i]);
				}
				AddVisitedSpot(m_Knots.back());
			}
			break;
		case Direction::Right:
			for (u32 x = 0; x < amount; x++)
			{
				m_Knots[0].x += 1;
				for (u32 i = 1; i < m_Knots.size(); i++)
				{
					MoveKnot(m_Knots[i - 1], m_Knots[i]);
				}
				AddVisitedSpot(m_Knots.back());
			}
			break;
		case Direction::Up:
			for (u32 y = 0; y < amount; y++)
			{
				m_Knots[0].y += 1;
				for (u32 i = 1; i < m_Knots.size(); i++)
				{
					MoveKnot(m_Knots[i - 1], m_Knots[i]);
				}
				AddVisitedSpot(m_Knots.back());
			}
			break;
		case Direction::Down:
			for (u32 y = 0; y < amount; y++)
			{
				m_Knots[0].y -= 1;
				for (u32 i = 1; i < m_Knots.size(); i++)
				{
					MoveKnot(m_Knots[i - 1], m_Knots[i]);
				}
				AddVisitedSpot(m_Knots.back());
			}
			break;
		}
	}

	void Rope::MoveKnot(const Point& head, Point& tail)
	{
		// Do nothing if head and tail are overlapping
		if (head.x == tail.x && head.y == tail.y)
		{
			// fmt::print("    H & T overlap - head: ({}, {}), tail: ({}, {})\n", head.x, head.y, tail.x, tail.y);
			return;
		}

		// Do nothing if head and tail are touching
		const i32 horizontalDifference = head.x - tail.x;
		const i32 verticalDifference = head.y - tail.y;
		if (abs(horizontalDifference) <= 1 && abs(verticalDifference) <= 1)
		{
			// fmt::print("    H & T touch   - head: ({}, {}), tail: ({}, {})\n", head.x, head.y, tail.x, tail.y);
			return;
		}

		// If head and tail are in the same column or row, move left right up or down
		if (head.x == tail.x || head.y == tail.y)
		{
			// If on same y, move on x
			if (head.y == tail.y)
			{
				tail.x += std::clamp(horizontalDifference, -1, 1);
			}

			// If on same x, move on y
			if (head.x == tail.x)
			{
				tail.y += std::clamp(verticalDifference, -1, 1);
			}

			// fmt::print("    move cardinal - head: ({}, {}), tail: ({}, {})\n", head.x, head.y, tail.x, tail.y);
		}
		// Otherwise they are in diagonal positions, and we should move diagonally
		else
		{
			tail.x += std::clamp(horizontalDifference, -1, 1);
			tail.y += std::clamp(verticalDifference, -1, 1);

			// fmt::print("    move diagonal - head: ({}, {}), tail: ({}, {})\n", head.x, head.y, tail.x, tail.y);
		}
	}

	void Rope::AddVisitedSpot(const Point& spot)
	{
		const auto it = std::ranges::find_if(m_VisitedSpots, [&](const Point& p)
		{
			return p.x == spot.x && p.y == spot.y;
		});

		if (it == m_VisitedSpots.end())
		{
			m_VisitedSpots.push_back(spot);
		}
	}
}
