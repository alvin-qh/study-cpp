#include <cmath>

#include "oop/class.hpp"

namespace cpp {
	Vector2D::Vector2D() :
		_x(0),
		_y(0),
		__destroy_count(nullptr) {
	}

	Vector2D::Vector2D(double x, double y) :
		_x(x),
		_y(y),
		__destroy_count(nullptr) {
		// 另一种形式的成员变量赋值
		// _x = x;
		// _y = y;
	}

	// 在拷贝构造器中调用参数构造器
	Vector2D::Vector2D(const Vector2D& o) :
		Vector2D(o._x, o._y) {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	Vector2D::~Vector2D() {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	Vector2D& Vector2D::operator=(const Vector2D& o) {
		if (this != &o) {
			_x = o._x;
			_y = o._y;
		}
		return *this;
	}

	bool Vector2D::operator==(const Vector2D& o) const {
		if (this == &o) {
			return true;
		}
		return _x == o._x && _y == o._y;
	}

	double Vector2D::length() const {
		return sqrt(_x * _x + _y * _y);
	}
} // namespace cpp
