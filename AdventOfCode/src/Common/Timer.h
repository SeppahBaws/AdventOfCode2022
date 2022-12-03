#pragma once
#include <chrono>

namespace Common
{
	class Timer
	{
	public:
		Timer();

		void Reset();

		[[nodiscard]] f64 PollNs() const;
		[[nodiscard]] f64 PollMs() const;

	private:
		std::chrono::high_resolution_clock::time_point m_Start;
	};
	
}
