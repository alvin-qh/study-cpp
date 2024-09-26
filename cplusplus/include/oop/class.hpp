#pragma once

#ifndef __CPLUSPLUS_OOP_CLASS_H
#define __CPLUSPLUS_OOP_CLASS_H

#include <type_traits>

namespace cpp {
	class Vector3D {
	private:
		double _x;
		double _y;
		double _z;

	public:
		/**
		 * 默认构造器
		 */
		Vector3D();

		/**
		 * 参数构造器
		 */
		Vector3D(double x, double y, double z);

		/**
		 * 获取 `_x` 字段值
		 */
		double x() const;

		/**
		 * 获取 `_y` 字段值
		 */
		double y() const;

		/**
		 * 获取 `_z` 字段值
		 */
		double z() const;
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_OOP_CLASS_H
