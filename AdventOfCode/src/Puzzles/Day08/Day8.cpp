#include "pch.h"
#include "Day8.h"

#include "Common/FileUtils.h"
#include <fmt/core.h>

namespace Day8
{
	typedef std::vector<std::vector<u32>> TreeGrid;

	bool IsVisibleFromOutside(const TreeGrid& grid, const u32 col, const u32 row)
	{
		// If on the edge, it's always visible from outside of the grid
		if (col == 0 || row == 0 || col == grid[row].size() - 1 || row == grid.size() - 1)
		{
			return true;
		}

		const u32 treeHeight = grid[row][col];
		bool visibleLeft = true;
		bool visibleRight = true;
		bool visibleTop = true;
		bool visibleBottom = true;

		for (u32 left = 0; left < col; left++)
		{
			if (grid[row][left] >= treeHeight)
			{
				visibleLeft = false;
				break;
			}
		}

		for (u32 right = col + 1; right < grid[row].size(); right++)
		{
			if (grid[row][right] >= treeHeight)
			{
				visibleRight = false;
				break;
			}
		}

		for (u32 top = 0; top < row; top++)
		{
			if (grid[top][col] >= treeHeight)
			{
				visibleTop = false;
				break;
			}
		}

		for (u32 bottom = row + 1; bottom < grid.size(); bottom++)
		{
			if (grid[bottom][col] >= treeHeight)
			{
				visibleBottom = false;
				break;
			}
		}

		return visibleLeft || visibleRight || visibleTop || visibleBottom;
	}

	u32 CalculateScenicScore(const TreeGrid& grid, const u32 col, const u32 row)
	{
		// If on the edge, it's always going to have a score of 0
		if (col == 0 || row == 0 || col == grid[row].size() - 1 || row == grid.size() - 1)
		{
			return 0;
		}

		// Default values to seeing outside of the grid
		u32 scoreLeft = col;
		u32 scoreTop = row;
		u32 scoreRight = grid[col].size() - col - 1;
		u32 scoreBottom = grid.size() - row - 1;
		const u32 treeHeight = grid[row][col];

		for (u32 left = col - 1; left > 0; --left)
		{
			if (grid[row][left] >= treeHeight)
			{
				scoreLeft = col - left;
				break;
			}
		}

		for (u32 right = col + 1; right < grid[row].size(); ++right)
		{
			if (grid[row][right] >= treeHeight)
			{
				scoreRight = right - col;
				break;
			}
		}

		for (u32 top = row - 1; top > 0; --top)
		{
			if (grid[top][col] >= treeHeight)
			{
				scoreTop = row - top;
				break;
			}
		}

		for (u32 bottom = row + 1; bottom < grid.size(); ++bottom)
		{
			if (grid[bottom][col] >= treeHeight)
			{
				scoreBottom = bottom - row;
				break;
			}
		}

		return scoreLeft * scoreRight * scoreTop * scoreBottom;
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 8 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day08/input.txt", lines);

		// inner vector is row, outer vector is column.
		TreeGrid trees{};

		for (std::string& line : lines)
		{
			auto& row = trees.emplace_back();
			for (char c : line)
			{
				row.push_back(c - '0');
			}
		}

		fmt::print("\n-----[ Part 1 ]-----\n");

		u32 nrTreesVisible = 0;

		for (u32 row = 0; row < trees.size(); row++)
		{
			for (u32 col = 0; col < trees[row].size(); col++)
			{
				if (IsVisibleFromOutside(trees, col, row))
				{
					nrTreesVisible++;
				}
			}
		}

		fmt::print("The amount of trees visible from outside the grid: {}\n", nrTreesVisible);


		fmt::print("\n-----[ Part 2 ]-----\n");

		u32 highestScenicScore = 0;
		for (u32 row = 0; row < trees.size(); row++)
		{
			for (u32 col = 0; col < trees[row].size(); col++)
			{
				const u32 score = CalculateScenicScore(trees, col, row);
				if (score > highestScenicScore)
				{
					highestScenicScore = score;
				}
			}
		}

		fmt::print("The highest possible scenic score is {}\n", highestScenicScore);
	}
}
