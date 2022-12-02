#include "pch.h"
#include "Day2.h"

#include <fmt/core.h>

#include "Common/FileUtils.h"

namespace Day2
{
	enum class Hand : u32
	{
		Rock = 1,
		Paper = 2,
		Scissors = 3
	};

	enum class Result : u32
	{
		Win = 6,
		Draw = 3,
		Lose = 0
	};

	Result CalculateGameResult(Hand myHand, Hand otherHand)
	{
		if (myHand == otherHand) return Result::Draw;

		switch (myHand)
		{
		case Hand::Rock:
			if (otherHand == Hand::Scissors) return Result::Win;
			return Result::Lose;
		case Hand::Paper:
			if (otherHand == Hand::Rock) return Result::Win;
			return Result::Lose;
		case Hand::Scissors:
			if (otherHand == Hand::Paper) return Result::Win;
			return Result::Lose;
		}

		throw std::runtime_error("Invalid combination");
	}

	Hand HandToPlayForResulT(Hand otherHand, Result desiredResult)
	{
		if (desiredResult == Result::Draw) return otherHand;

		switch (otherHand)
		{
		case Hand::Rock:
			if (desiredResult == Result::Win) return Hand::Paper;
			return Hand::Scissors;
		case Hand::Paper:
			if (desiredResult == Result::Win) return Hand::Scissors;
			return Hand::Rock;
		case Hand::Scissors:
			if (desiredResult == Result::Win) return Hand::Rock;
			return Hand::Paper;
		}

		throw std::runtime_error("Invalid combination");
	}

	// X, Y and Z are for the first part
	Hand HandFromInput(char input)
	{
		switch (input)
		{
		case 'A':
		case 'X':
			return Hand::Rock;
		case 'B':
		case 'Y':
			return Hand::Paper;
		case 'C':
		case 'Z':
			return Hand::Scissors;
		default: break;
		}

		throw std::runtime_error("Invalid input string");
	}

	// Only used for the second part
	Result ResultFromInput(char input)
	{
		switch (input)
		{
		case 'X': return Result::Lose;
		case 'Y': return Result::Draw;
		case 'Z': return Result::Win;
		default: break;
		}

		throw std::runtime_error("Invalid input string!");
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 2 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day02/input.txt", lines);

		fmt::print("\n-----[ Part 1 ]-----\n");

		u32 totalScore = 0;
		for (const std::string& line : lines)
		{
			// Validate input
			if (line.length() < 3)
			{
				fmt::print("ERROR: line was smaller than 3 characters!!!\nline: '{}'\n", line);
				return;
			}

			// what comes from A B or C
			const Hand otherHand = HandFromInput(line[0]);
			// what comes from X Y or Z
			const Hand myHand = HandFromInput(line[2]);

			const u32 score =
				static_cast<u32>(CalculateGameResult(myHand, otherHand)) // Score from the result of the game
				+ static_cast<u32>(myHand); // Score from the played hand
			totalScore += score;
		}

		fmt::print("My total score over the entire game is {}\n", totalScore);

		fmt::print("\n-----[ Part 2 ]-----\n");

		totalScore = 0;
		for (const std::string& line : lines)
		{
			const Hand otherHand = HandFromInput(line[0]);
			const Result desiredResult = ResultFromInput(line[2]);

			const Hand myHand = HandToPlayForResulT(otherHand, desiredResult);

			const u32 score =
				static_cast<u32>(CalculateGameResult(myHand, otherHand)) // Score from the result of the game
				+ static_cast<u32>(myHand); // Score from the played hand
			totalScore += score;
		}

		fmt::print("Adjusted for the new rules, my new score is {}\n", totalScore);
	}
}
