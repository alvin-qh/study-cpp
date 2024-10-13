#pragma once

#ifndef __CPLUSPLUS_OPP_OPERATOR_H
#define __CPLUSPLUS_OPP_OPERATOR_H

#include <memory>

namespace cpp::oop {
	/// @brief 定义类, 演示运算符重载
	class Operator {
	private:
		double _x, _y, _z;
	public:
		/// @brief 默认构造器
		Operator();

		/// @brief 参数构造器
		///
		/// @param x x 参数 1
		/// @param y y 参数 2
		/// @param z z 参数 3
		Operator(double x, double y, double z);

		/// @brief 拷贝构造器
		///
		/// 使用默认拷贝构造器
		Operator(const Operator&) = default;

		/// @brief 析构函数
		///
		/// 使用默认析构函数
		virtual ~Operator() = default;

		/// @brief 赋值运算符重载
		///
		/// 使用默认赋值运算符重载
		///
		/// @param right 另一个对象实例
		/// @return 当前对象引用
		Operator& operator=(const Operator& right) = default;

		/// @brief 加法运算符重载
		///
		/// @param right 作为加数的对象实例
		/// @return 加法运算结果, 为当前类型的新对象
		Operator operator+(const Operator& right) const;

		/// @brief 减法运算符重载
		///
		/// C++ 支持全局运算符重载, 为了让全局运算符重载函数可以访问当前类私有成员,
		/// 可以全局运算符重载函数其定义为当前类的 "友元函数"
		///
		/// @param left 被加数对象实例
		/// @param right 加数对象实例
		/// @return 减运算结果, 为当前类型的新对象
		friend Operator operator-(const Operator& left, const Operator& right);

		/// @brief 重载乘法运算符
		///
		/// 该运算符重载表示当前对象"乘以"一个浮点数
		///
		/// @param scale 浮点数乘数
		/// @return 相乘结果, 为当前类型的新对象
		Operator operator*(double scale) const;

		/// @brief 重载乘法运算符
		///
		/// 该运算符重载表示当前对象和另一个对象相乘
		///
		/// @param right 作为乘数的对象引用
		/// @return 两个对象相乘的结果, 为一个浮点数值
		double operator*(const Operator& right) const;

		/// @brief 重载下标运算符
		///
		/// `0 => x`
		/// `1 => y`
		/// `2 => z`
		///
		/// @param index 下标值
		/// @return 下标对应的变量值
		double operator[](int index) const;

		double x() const;
		double y() const;
		double z() const;
	};

	/// @brief 全局运算符重载, 重载 `Vector3D` 类型的 `-` 运算符
	///
	/// 全局运算符重载必须符合如下要求:
	///
	/// 1. 参数必须为自定义类型, 而非 C++ 基本类型;
	///
	/// 2. 参数定义必须符合运算符左右值的要求;
	///
	/// 3. 如果需要访问相关类型的私有成员, 需要在相关类型中定义全局运算符重载函数为友元函数;
	///
	/// @param left
	/// @param right
	/// @return 两个对象相减的结果
	Operator operator-(const Operator& left, const Operator& right);
} // ! namespace cpp::oop

#endif // ! __CPLUSPLUS_OPP_OPERATOR_H
