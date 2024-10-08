#pragma once

#ifndef __CPLUSPLUS_OOP_CLASS_H
#define __CPLUSPLUS_OOP_CLASS_H

#include <cstdint>

namespace cpp {
	/// @brief 定义 2D 坐标点类
	class Point2D {
	protected:
		double _x;
		double _y;
		uint32_t* __destroy_count;
	public:
		/// @brief 默认构造器
		Point2D();

		/// @brief 参数构造器
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		Point2D(double x, double y);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个同类型对象
		Point2D(const Point2D& o);

		/// @brief 析构函数
		///
		/// 析构函数一般声明为 `virtual`,
		/// 表示其为一个虚函数,
		/// 这样当前类的子类的析构函数调用时,
		/// 也会调用父类的析构函数
		virtual ~Point2D();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个同类型对象
		/// @return 当前对象的引用
		Point2D& operator=(const Point2D& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个同类型对象
		/// @return 两个对象是否相同
		bool operator==(const Point2D& o) const;

		/// @brief 设置析构数量记录变量指针
		///
		/// @param destroy_count 整数变量指针
		void __set_destroy_count_ref(uint32_t* destroy_count);

		/// @brief 重新设置成员变量的值
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		void set(double x, double y);

		/// @brief 计算点表示的向量的模
		///
		/// @return 向量的模
		virtual double norm() const;

		/// @brief 获取 `_x` 字段值
		///
		/// @return `x` 坐标值
		double x() const;

		/// @brief 获取 `_y` 字段值
		///
		/// @return `y` 坐标值
		double y() const;
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_OOP_CLASS_H
