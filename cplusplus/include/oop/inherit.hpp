#pragma once

#ifndef __CPLUSPLUS_OOP_INHERIT_H
#define __CPLUSPLUS_OOP_INHERIT_H

#include "class.hpp"

namespace cpp {
	/// @brief 定义 3D 坐标点类
	class Point3D : public Point2D {
	private:
		double _z;
	public:
		/// @brief 默认构造器
		Point3D();

		/// @brief 参数构造器
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		/// @param z `z` 坐标值
		Point3D(double x, double y, double z);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个同类型对象
		Point3D(const Point3D& o);

		/// @brief 析构函数
		///
		/// 虚拟析构函数在调用时, 会自动调用父类析构函数
		virtual ~Point3D();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个同类型对象
		/// @return 当前对象的引用
		Point3D& operator=(const Point3D& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个同类型对象
		/// @return 两个对象是否相同
		bool operator==(const Point3D& o) const;

		/// @brief 令 `Point3D` 实例和 `Point2D` 不相等
		///
		/// @return 不相等
		bool operator==(const Point2D&) const;

		/// @brief 重新设置成员变量的值
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		/// @param z `z` 坐标值
		void set(double x, double y, double z);

		/// @brief 计算点所表示向量的模
		///
		/// `override` 表示该函数一定会重写父类的同名函数, 否则会报告编译错误
		///
		/// @return 向量的模
		virtual double norm() const override;

		/// @brief 获取 `_z` 字段值
		///
		/// @return `z` 坐标的值
		double z() const;
	};
}

#endif // ! __CPLUSPLUS_OOP_INHERIT_H
