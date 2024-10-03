#include <stdint.h>
#include <cmath>

#include "oop/class.hpp"

namespace cpp {
	/// Vector2D implement

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

	/// Vector3D implement

	Vector3D::Vector3D() :
		Vector2D(),
		_z(0) {
	}

	Vector3D::Vector3D(double x, double y, double z) :
		Vector2D(x, y),
		_z(z) {
	}

	Vector3D::Vector3D(const Vector3D& o) :
		Vector2D(o),
		_z(o._z) {
	}

	Vector3D::~Vector3D() {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	Vector3D& Vector3D::operator=(const Vector3D& o) {
		Vector2D::operator=(o);
		_z = o._z;
		return *this;
	}

	bool Vector3D::operator==(const Vector3D& o) const {
		if (!Vector2D::operator==(o)) {
			return false;
		}
		return _z == o._z;
	}

	double Vector3D::length() const {
		return sqrt(_x * _x + _y * _y + _z * _z);
	}
} // namespace cpp
