#pragma once

namespace Day5
{
	void Run();

	struct Command
	{
		u32 amount;
		u32 fromStack;
		u32 toStack;
	};

	class ContainerStack
	{
	public:
		explicit ContainerStack(const std::vector<std::string>& inputLines);

		void Move(u32 amount, u32 fromStack, u32 toStack, bool keepOrder);
		void ResetState();

		[[nodiscard]] std::string GetStatus() const;

	private:
		std::array<std::vector<char>, 9> m_Stacks;
		const std::vector<std::string>& m_InputLines;
	};
}
