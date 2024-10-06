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

	Vector3D Vector3D::operator*(double scalar) const {
		return Vector3D(
			_x * scalar,
			_y * scalar,
			_z * scalar
		);
	}

	double Vector3D::operator*(const Vector3D& right) const {
		return _x * right._x + _y * right._y + _z * right._z;
	}

	double Vector3D::operator[](int index) {
		switch (index) {
		case 0:
			return _x;
		case 1:
			return _y;
		case 2:
			return _z;
		default:
			throw std::out_of_range("Index out of range");
		}
	}

	double Vector3D::operator[](int index) const {
		return const_cast<Vector3D*>(this)->operator[](index);
	}

	double Vector3D::x() const { return _x; }
	double Vector3D::y() const { return _y; }
	double Vector3D::z() const { return _z; }
}
