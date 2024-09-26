#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "oop/class.hpp"

namespace cpp {
	Vector3D::Vector3D() {
	}

	Vector3D::Vector3D(double x, double y, double z) {
		this->_x = x;
		this->_y = y;
		this->_z = z;
	}

	double Vector3D::x() const {
		return this->_x;
	}

	double Vector3D::y() const {
		return this->_y;
	}

	double Vector3D::z() const {
		return this->_z;
	}
} // ! namespace cpp

#pragma clang diagnostic pop
