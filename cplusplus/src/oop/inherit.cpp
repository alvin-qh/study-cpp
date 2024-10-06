#include <cmath>

#include "oop/inherit.hpp"

namespace cpp {
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
