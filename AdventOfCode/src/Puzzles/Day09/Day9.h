#pragma once

namespace Day9
{
	void Run();

	struct Point
	{
		i32 x;
		i32 y;
	};

	enum class Direction
	{
		Left,
		Right,
		Up,
		Down,
	};

	class Rope
	{
	public:
		Rope(u32 nrOfKnots)
			: m_Knots(nrOfKnots + 1)
		{
		}

		void SimulateMovement(Direction direction, u32 amount);

		[[nodiscard]] const std::vector<Point>& GetVisitedSpots() const { return m_VisitedSpots; }

	private:
		void MoveKnot(const Point& head, Point& tail);
		void AddVisitedSpot(const Point& spot);

	private:
		std::vector<Point> m_Knots{};
		std::vector<Point> m_VisitedSpots{{}};
	};
}
