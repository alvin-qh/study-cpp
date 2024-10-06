#pragma once

#ifndef __CPLUSPLUS_OPP_OPERATOR_H
#define __CPLUSPLUS_OPP_OPERATOR_H

#include <memory>

namespace cpp {
	/// @brief 定义 3D 向量类, 测试运算符重载
	class Vector3D {
	private:
		double _x, _y, _z;
	public:
		/// @brief 默认构造器
		Vector3D();

		/// @brief 参数构造器
		///
		/// @param x x 轴分量
		/// @param y y 轴分量
		/// @param z z 轴分量
		Vector3D(double x, double y, double z);

		/// @brief 拷贝构造器
		///
		/// 使用默认拷贝构造器
		Vector3D(const Vector3D&) = default;

		/// @brief 析构函数
		///
		/// 使用 C++ 默认析构函数
		virtual ~Vector3D() = default;

		/// @brief 赋值运算符重载
		///
		/// @param right 另一个对象实例
		/// @return 当前对象引用
		Vector3D& operator=(const Vector3D& right) = default;

		/// @brief 加法运算符重载
		///
		/// @param right 作为加数的对象实例
		/// @return 向量相加的结果向量
		Vector3D operator+(const Vector3D& right) const;

		/// @brief 减法运算符重载
		///
		/// C++ 支持全局运算符重载, 为了让全局运算符重载函数可以访问当前类私有成员,
		/// 可以全局运算符重载函数其定义为当前类的 "友元函数"
		///
		/// @param left 被加数对象实例
		/// @param right 加数对象实例
		/// @return 向量相加的结果向量
		friend Vector3D operator-(const Vector3D& left, const Vector3D& right);

		/// @brief 重载乘法运算符
		///
		/// 定义向量放大, 即一个向量乘以一个标量, 得到放大后的向量
		///
		/// @param scale 放大系数
		/// @return 放大后的向量
		Vector3D operator*(double scale) const;

		/// @brief 重载乘法运算符
		///
		/// 定义向量的点积
		///
		/// @param right 相乘的向量对象实例
		/// @return 点积结果标量
		double operator*(const Vector3D& right) const;

		/// @brief 重载下标运算符
		///
		/// `0 => x`
		/// `1 => y`
		/// `2 => z`
		///
		/// @param index 下标值
		/// @return 下标对应的分量值
		double operator[](int index);

		/// @brief 重载下标运算符 (当前对象只读时)
		///
		/// @param index 下标值
		/// @return 下标对应的分量值
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
	Vector3D operator-(const Vector3D& left, const Vector3D& right);
}

#endif // ! __CPLUSPLUS_OPP_OPERATOR_H
