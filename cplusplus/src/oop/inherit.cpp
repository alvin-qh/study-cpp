#include <cmath>

#include "oop/inherit.hpp"

namespace cpp {
	Point3D::Point3D() :
		Point2D(), // 调用父类默认构造器
		_z(0) {
	}

	Point3D::Point3D(double x, double y, double z) :
		Point2D(x, y), // 调用父类参数构造器
		_z(z) {
	}

	Point3D::Point3D(const Point3D& o) :
		Point2D(o), // 调用父类拷贝构造器
		_z(o._z) {
	}

	Point3D::~Point3D() {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	Point3D& Point3D::operator=(const Point3D& o) {
		Point2D::operator=(o);
		_z = o._z;
		return *this;
	}

	bool Point3D::operator==(const Point3D& o) const {
		if (!Point2D::operator==(o)) {
			return false;
		}
		return _z == o._z;
	}

	bool Point3D::operator==(const Point2D&) const {
		return false;
	}

	void Point3D::set(double x, double y, double z) {
		Point2D::set(x, y);
		_z = z;
	}

	double Point3D::norm() const {
		return sqrt(_x * _x + _y * _y + _z * _z);
	}

	double Point3D::z() const {
		return _z;
	}
} // namespace cpp
