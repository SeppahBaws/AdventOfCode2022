#pragma once
#include <optional>

namespace Day11
{
	void Run();

	struct Monkey
	{
		std::vector<u64> startingItems;
		char operation;
		// std::nullopt to use the old value.
		std::optional<u32> operationValue;
		u32 divisibleBy;
		u32 throwToWhenTrue;
		u32 throwToWhenFalse;

		u64 nrOfItemsInspected{ 0 };
	};
}
