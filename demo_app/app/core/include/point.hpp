#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <cstring>

namespace Lcd {

	class Point {
	private:
		size_t x_, y_;
	public:
		Point(size_t x, size_t y);
		size_t x() const;
		size_t y() const;
		void set_x(size_t x);
		void set_y(size_t y);

		size_t square() const;

		const Point operator+(const Point &point);
		const Point operator-(const Point &point);
		const Point &operator+=(const Point &point); 
	};
}

#endif

