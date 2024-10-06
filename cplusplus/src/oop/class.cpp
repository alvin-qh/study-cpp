#include <cmath>

#include "oop/class.hpp"

namespace cpp {
	Point2D::Point2D() :
		_x(0),
		_y(0),
		__destroy_count(nullptr) {
	}

	Point2D::Point2D(double x, double y) :
		_x(x),
		_y(y),
		__destroy_count(nullptr) {
		// 另一种形式的成员变量赋值
		// _x = x;
		// _y = y;
	}

	// 在拷贝构造器中调用参数构造器
	Point2D::Point2D(const Point2D& o) :
		Point2D(o._x, o._y) {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	Point2D::~Point2D() {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	Point2D& Point2D::operator=(const Point2D& o) {
		if (this != &o) {
			_x = o._x;
			_y = o._y;
		}
		return *this;
	}

	bool Point2D::operator==(const Point2D& o) const {
		if (this == &o) {
			return true;
		}
		return _x == o._x && _y == o._y;
	}

	void Point2D::__set_destroy_count_ref(uint* destroy_count) {
		__destroy_count = destroy_count;
	}

	void Point2D::set(double x, double y) {
		_x = x;
		_y = y;
	}

	double Point2D::norm() const {
		return sqrt(_x * _x + _y * _y);
	}

	double Point2D::x() const {
		return _x;
	}

	double Point2D::y() const {
		return _y;
	}
} // namespace cpp
