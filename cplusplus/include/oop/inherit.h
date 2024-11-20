#pragma once

#ifndef __CPLUSPLUS_OOP__INHERIT_H
#define __CPLUSPLUS_OOP__INHERIT_H

#include <cstdint>
#include <string>

namespace cxx::oop {

	/// @brief 定义父类
	class BaseClass {
	protected:
		int _a;
		uint32_t* __destroy_count_ptr;
	public:
		/// @brief 默认构造器
		BaseClass();

		/// @brief 参数构造器
		///
		/// @param a 参数值, 对应 `_a` 字段
		BaseClass(int a);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个对象引用
		BaseClass(const BaseClass& o);

		/// @brief 虚析构函数
		///
		/// 将虚构函数定义为虚函数, 是为了子类在重写析构函数后,
		/// 子类对象在析构时, 自动调用父类析构函数
		virtual ~BaseClass();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个对象引用
		/// @return 当前对象引用
		BaseClass& operator=(const BaseClass& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个对象引用
		/// @return 两个对象是否相等
		bool operator==(const BaseClass& o) const;

		/// @brief 设置整数指针用于记录析构次数
		///
		/// @param destroy_count 指向记录析构次数值的指针
		void __set_destroy_count_ptr(uint32_t* destroy_count);

		/// @brief 将当前对象转为字符串
		///
		/// 该函数定义为虚函数, 是为了子类可以对其进行重写
		///
		/// @return 字符串值
		virtual std::string to_string() const;

		/// @brief 获取 `A` 字段值
		///
		/// @return `_a` 字段值
		int a() const;
	protected:
		void __increment_destroy_count();
	};

	/// @brief 定义子类
	class ChildClass : public BaseClass {
	public:
		/// @brief 默认构造器
		ChildClass();

		/// @brief 参数构造器
		///
		/// @param a 参数值, 对应 `BaseClass::_a` 字段
		/// @param b 参数值, 对应 `ChildClass::_b` 字段
		ChildClass(int a, double b);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个同类型对象
		ChildClass(const ChildClass& o);

		/// @brief 析构函数
		///
		/// 虚拟析构函数在调用时, 会自动调用父类析构函数
		virtual ~ChildClass();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个同类型对象
		/// @return 当前对象的引用
		ChildClass& operator=(const ChildClass& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个同类型对象
		/// @return 两个对象是否相同
		bool operator==(const ChildClass& o) const;

#if !__ge_cxx20
		/// @brief 对于 C++ 20 以下版本, 编译器不会自动生成不等号运算符重载
		bool operator!=(const ChildClass& o) const;
#endif

		/// @brief 令 `ChildClass` 实例和 `BaseClass` 不相等
		///
		/// @return 不相等
		bool operator==(const BaseClass&) const = delete;

		/// @brief 重新设置成员变量的值
		///
		/// @param b `b` 参数值, 对应 `_b` 字段
		void set_b(double b);

		/// @brief 获取 `_b` 字段值
		///
		/// @return `b` 字段值
		double b() const;

		/// @brief 重写父类虚函数
		///
		/// `override` 表示该函数一定会重写父类的同名函数, 否则会报告编译错误
		///
		/// @return 字符串对象
		virtual std::string to_string() const override;

	private:
		double _b;
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OOP_INHERIT_H
