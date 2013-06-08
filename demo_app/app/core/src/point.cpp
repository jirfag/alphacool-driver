#include "point.hpp"


namespace Lcd {

	Point::Point(size_t x, size_t y) : x_(x), y_(y) { }
	size_t Point::x() const { return x_; }
	size_t Point::y() const { return y_; }

	void Point::set_x(size_t x) { x_ = x; }
	void Point::set_y(size_t y) { y_ = y; }

	size_t Point::square() const { return x_ * y_; }

	const Point Point::operator+(const Point &point)
   	{
		return Point(x() + point.x(), y() + point.y());
	}

	const Point Point::operator-(const Point &point)
   	{
		return Point(x() - point.x(), y() - point.y());
	}

	const Point &Point::operator+=(const Point &point)
   	{
		set_x(x() + point.x());
		set_y(y() + point.y());
		return *this;
	}
}
