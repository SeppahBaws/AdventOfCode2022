#pragma once
#include <optional>

namespace Day10
{
	void Run();

	enum class Operation
	{
		Noop,
		Addx
	};

	class Computer
	{
	public:
		Computer();

		void Reset();

		void DoNoop();
		void DoAddx(i32 amount);

		[[nodiscard]] u32 GetPart1Total() const { return m_Part1Total; }
		void PrintScreen() const;

	private:
		void EvaluateCycle();

	private:
		i32 m_Register;
		u32 m_Cycle;

		u32 m_Part1Total{};

		std::array<std::array<char, 40>, 6> m_Screen;
	};
}
