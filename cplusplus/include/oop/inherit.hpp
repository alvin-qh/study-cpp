#pragma once

#ifndef __CPLUSPLUS_OOP_INHERIT_H
#define __CPLUSPLUS_OOP_INHERIT_H

#include "class.hpp"

namespace cpp {
	/// @brief 定义 3D 向量类
	class Vector3D : public Vector2D {
	private:
		double _z;
	public:
		/// @brief 默认构造器
		Vector3D();

		/// @brief 参数构造器
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		/// @param z `z` 坐标值
		Vector3D(double x, double y, double z);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个同类型对象
		Vector3D(const Vector3D& o);

		/// @brief 析构函数
		virtual ~Vector3D();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个同类型对象
		/// @return 当前对象的引用
		Vector3D& operator=(const Vector3D& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个同类型对象
		/// @return 两个对象是否相同
		bool operator==(const Vector3D& o) const;

		/// @brief 令 `Vector3D` 实例和 `Vector2D` 不相等
		///
		/// @return 不相等
		inline bool operator==(const Vector2D&) const { return false; }

		/// @brief 重新设置成员变量的值
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		/// @param z `z` 坐标值
		inline void set(double x, double y, double z) {
			Vector2D::set(x, y);
			_z = z;
		}

		/// @brief 获取 `_z` 字段值
		///
		/// @return `z` 坐标的值
		inline double z() const { return _z; };

		/// @brief 计算向量长度
		///
		/// @return 向量长度
		virtual double length() const override;
	};
}

#endif // ! __CPLUSPLUS_OOP_INHERIT_H
