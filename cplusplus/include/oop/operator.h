#pragma once

#ifndef __CPLUSPLUS_OPP__OPERATOR_H
#define __CPLUSPLUS_OPP__OPERATOR_H

#include <memory>

namespace cxx::oop {

	/// @brief 定义类, 演示运算符重载
	class Operator {
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

		/// @brief 拷贝赋值运算符重载
		///
		/// 使用默认拷贝赋值运算符重载
		///
		/// @param right 另一个对象实例
		/// @return 当前对象引用
		Operator& operator=(const Operator& right) = default;

		/// @brief 移动赋值运算符重载
		///
		/// 将 `right` 对象移动到当前对象
		///
		/// @param right 被移动的对象右值引用
		/// @return 当前对象引用
		Operator& operator=(Operator&& right) noexcept;

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

		/// @brief 重载前置自增运算符
		///
		/// @return 当前对象引用
		Operator& operator++() noexcept;

		/// @brief 重载后置自增运算符
		///
		/// @return 当前对象副本
		Operator operator++(int) noexcept;

		/// @brief 重载前置自减运算符
		///
		/// @return 当前对象引用
		Operator& operator--() noexcept;

		/// @brief 重载后置自减运算符
		///
		/// @return 当前对象副本
		Operator operator--(int) noexcept;

		/// @brief 重载加法运算符, 允许当前对象和一个三元组对象进行相加
		///
		/// @param right 三元组对象引用
		/// @return 结果对象实例
		Operator operator+(const std::tuple<double, double, double>& right) const noexcept;

		/// @brief 将加法运算符重载设置为友元函数
		///
		/// @param right 当前类型对象引用
		/// @return 结果对象实例
		friend Operator operator+(const std::tuple<double, double, double>& left, const Operator& right);

		/// @brief 重载减法运算符, 允许当前对象和一个三元组对象进行相减
		///
		/// @param right 三元组对象引用
		/// @return 结果对象实例
		Operator operator-(const std::tuple<double, double, double>& right) const noexcept;

		/// @brief 将减法运算符重载设置为友元函数
		///
		/// @param right 当前类型对象引用
		/// @return 结果对象实例
		friend Operator operator-(const std::tuple<double, double, double>& left, const Operator& right);

		/// @brief 重载判等运算符
		///
		/// @param right 待比较的对象引用
		/// @return 是否相等
		bool operator==(const Operator& right) const noexcept;

#if __ge_cxx20

		/// @brief 重载三路比较运算符
		///
		/// 三路运算符可以同时进行 `==`, `!=`, `<`, `>`, `<=`, `>=` 比较, 对于一个类来说, 如果重载了 `<=>` 和 `==`
		/// 运算符, 则可以自动生成全部的比较运算符
		///
		/// 三路运算符可以返回如下三类对象:
		///
		/// - `std::strong_ordering`: 强序性比较, 应比较所有成员字段, 等值结果唯一;
		/// - `std::weak_ordering`: 弱序性比较, 即对成员字段进计算后进行比较, 等值结果不唯一;
		/// - `std::partial_ordering`: 偏序性比较, 即忽略无法比较的成员进行比较, 等值结果不唯一;
		///
		/// 三路运算符在 C++20 以上支持
		///
		/// @param right 待比较的对象引用
		/// @return 表示比较结果的 `std::strong_ordering` 对象
		std::partial_ordering operator<=>(const Operator& right) const noexcept;

#else // 对于低于 C++20 版本, 则需要重载如下比较运算符

		/// @brief 重载小于运算符
		///
		/// @param right 待比较的对象引用
		/// @return 是否小于
		bool operator<(const Operator& right) const noexcept;

		/// @brief 重载小于等于运算符
		///
		/// @param right 待比较的对象引用
		/// @return 是否小于等于
		bool operator<=(const Operator& right) const noexcept;

		/// @brief 重载大于运算符
		///
		/// @param right 待比较的对象引用
		/// @return 是否大于
		bool operator>(const Operator& right) const noexcept;

		/// @brief 重载大于等于运算符
		///
		/// @param right 待比较的对象引用
		/// @return 是否大于等于
		bool operator>=(const Operator& right) const noexcept;

		/// @brief 重载不等于运算符
		///
		/// @param right 待比较的对象引用
		/// @return 是否不等于
		bool operator!=(const Operator& right) const noexcept;
#endif

		double x() const;
		double y() const;
		double z() const;

	private:
		double _x, _y, _z;
	};

	/// @brief 全局运算符重载, 重载 `Vector3D` 类型的 `-` 运算符
	///
	/// 全局运算符重载必须符合如下要求:
	///
	/// 1. 参数必须为自定义类型, 而非 C++ 基本类型;
	/// 2. 参数定义必须符合运算符左右值的要求;
	/// 3. 如果需要访问相关类型的私有成员, 需要在相关类型中定义全局运算符重载函数为友元函数;
	///
	/// @param left 待比较的对象引用
	/// @param right 待比较的对象引用
	/// @return 两个对象相减的结果
	Operator operator-(const Operator& left, const Operator& right);

	/// @brief 重载加法运算符, 允许一个三元组对象和 `Operator` 类型对象相加
	///
	/// @param left 三元组对象引用
	/// @param right `Operator` 对象引用
	/// @return 计算结果对象
	Operator operator+(const std::tuple<double, double, double>& left, const Operator& right);

	/// @brief 重载加法运算符, 允许一个三元组对象和 `Operator` 类型对象相减
	///
	/// @param left 三元组对象引用
	/// @param right `Operator` 对象引用
	/// @return 计算结果对象
	Operator operator-(const std::tuple<double, double, double>& left, const Operator& right);


	/// @brief 测试继承时运算符的继承情况
	class OperatorChild : public Operator {
	public:
		/// @brief 默认构造器
		OperatorChild();

		/// @brief 参数构造器
		///
		/// @param x 参数 1
		/// @param y 参数 2
		/// @param z 参数 3
		OperatorChild(double x, double y, double z);

		/// @brief 析构函数
		virtual ~OperatorChild() override = default;

		/// @brief 拷贝构造器
		OperatorChild(const OperatorChild&) = default;

		/// @brief 重载赋值运算符
		///
		/// 如果不明确重载赋值运算符, 子类会自动产生一个默认赋值运算符重载 (default),
		/// 故子类需显式定义赋值运算符重载, 并在重载方法内调用父类赋值运算符重载
		OperatorChild& operator=(const OperatorChild&) noexcept = default;

		/// @brief 重载移动赋值运算符
		///
		/// 如果不明确重载赋值运算符, 子类会自动产生一个默认赋值运算符重载 (default),
		/// 故子类需显式定义赋值运算符重载, 并在重载方法内调用父类赋值运算符重载
		OperatorChild& operator=(OperatorChild&&) noexcept = default;
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OPP__OPERATOR_H
