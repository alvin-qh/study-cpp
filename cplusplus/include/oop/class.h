#pragma once

#ifndef __CPLUSPLUS_OOP__CLASS_H
#define __CPLUSPLUS_OOP__CLASS_H

#include <cstdint>

namespace cxx::oop {

	/// @brief 定义一个类
	class AClass {
	protected:
		int _value;
		uint32_t* __destroy_count;
	public:
		/// @brief 默认构造器
		AClass();

		/// @brief 参数构造器
		///
		/// @param value `value` 参数值
		AClass(int value);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个同类型对象
		AClass(const AClass& o);

		/// @brief 析构函数
		///
		/// 析构函数一般声明为 `virtual`, 表示其为一个虚函数,
		/// 这样当前类的子类的析构函数调用时, 也会调用父类的析构函数
		virtual ~AClass();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个同类型对象
		/// @return 当前对象的引用
		AClass& operator=(const AClass& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个同类型对象
		/// @return 两个对象是否相同
		bool operator==(const AClass& o) const;

#if !__ge_cxx20
		/// @brief 在 C++ 20 版本以前, 编译器无法根据 `==` 重载自动产生 `!=` 重载, 需要自行定义
		bool operator!=(const AClass& o) const;
#endif

		/// @brief 设置 `_value` 字段的值
		///
		/// @param value 参数值
		void set_value(int value);

		/// @brief 获取 `_value` 字段值
		///
		/// @return `_value` 字段值
		double value() const;
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OOP__CLASS_H
