#include "oop/default.hpp"

namespace cpp {
	Point::Point() :
		_x(0),
		_y(0) {
	}

	Point::Point(double x, double y) :
		_x(x),
		_y(y) {
	}

	bool Point::operator==(const Point& o) const {
		return this == &o ? true : _x == o._x && _y == o._y;
	}

	double Point::x() const {
		return _x;
	}

	double Point::y() const {
		return _y;
	}
} // namespace cpp
