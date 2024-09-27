#pragma once

#ifndef __CPLUSPLUS_OPP_DEFAULT_H
#define __CPLUSPLUS_OPP_DEFAULT_H

namespace cpp {
	/// @brief 定义类测试默认函数
	class Point {
	private:
		double _x, _y;
	public:
		/// @brief 默认构造器
		Point()
			:_x(0)
			, _y(0) {}

		/// @brief 参数构造器
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		Point(double x, double y)
			: _x(x)
			, _y(y) {}

		/// @brief 定义拷贝构造函数
		///
		/// 可以通过 `default` 关键字简化拷贝构造器调用
		///
		/// @param o 同类型对象引用
		Point(const Point& o) = default;

		/// @brief 定义析构函数
		///
		/// 可以通过 `default` 关键字简化默认析构函数定义
		virtual ~Point() = default;

		/// @brief 重载赋值运算符
		///
		/// 可以通过 `default` 关键字简化赋值运算符重载
		///
		/// @param o 同类型对象引用
		/// @return 当前对象引用
		Point& operator=(const Point& o) = default;

		/// @brief 重载判等运算符
		///
		/// @param o 同类型对象引用
		/// @return `true` 表示相等，`false` 表示不相等
		bool operator==(const Point& o) const {
			return this == &o ? true : _x == o._x && _y == o._y;
		};

		/// @brief 获取 `x` 坐标值
		///
		/// @return `x` 坐标值
		double x() const { return _x; }

		/// @brief 获取 `y` 坐标值
		///
		/// @return `y` 坐标值
		double y() const { return _y; }
	};
}

#endif // !__CPLUSPLUS_OPP_DEFAULT_H
