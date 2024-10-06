#include "oop/operator.hpp"

namespace cpp {
	Vector3D::Vector3D() :
		_x(0),
		_y(0),
		_z(0) {
	}

	Vector3D::Vector3D(double x, double y, double z) :
		_x(x),
		_y(y),
		_z(z) {
	}

	Vector3D::~Vector3D() {
	}

	Vector3D Vector3D::operator+(const Vector3D& right) const {
		return Vector3D(
			_x + right._x,
			_y + right._y,
			_z + right._z
		);
	}

	Vector3D operator-(const Vector3D& left, const Vector3D& right) {
		return Vector3D(
			left._x - right._x,
			left._y - right._y,
			left._z - right._z
		);
	}
}
