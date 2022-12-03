#include "pch.h"
#include "Timer.h"

namespace Common
{
	Timer::Timer()
		: m_Start(std::chrono::high_resolution_clock::now())
	{
	}

	void Timer::Reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	f64 Timer::PollNs() const
	{
		const auto end = std::chrono::high_resolution_clock::now();
		
		const std::chrono::duration<f64> elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_Start);

		return elapsedTime.count();
	}

	f64 Timer::PollMs() const
	{
		const auto end = std::chrono::high_resolution_clock::now();
		
		const std::chrono::duration<f64> elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_Start);

		return elapsedTime.count();
	}
}
