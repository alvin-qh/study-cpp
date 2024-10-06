#pragma once

#ifndef __CPLUSPLUS_OPP_OPERATOR_H
#define __CPLUSPLUS_OPP_OPERATOR_H

#include <memory>

namespace cpp {
	class Vector3D {
	private:
		double _x, _y, _z;
	public:
		Vector3D();

		Vector3D(double x, double y, double z);

		Vector3D(const Vector3D&) = default;

		virtual ~Vector3D();

		Vector3D& operator=(const Vector3D&) = default;

		Vector3D operator+(const Vector3D&) const;

		friend Vector3D operator-(const Vector3D&, const Vector3D&);

		double x() const { return _x; }
		double y() const { return _y; }
		double z() const { return _z; }
	};

	Vector3D operator-(const Vector3D&, const Vector3D&);
}

#endif // ! __CPLUSPLUS_OPP_OPERATOR_H
