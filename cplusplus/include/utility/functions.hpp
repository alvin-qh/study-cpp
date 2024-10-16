#pragma once

#ifndef __CPLUSPLUS_UTILITY_FUNCTIONS_H
#define __CPLUSPLUS_UTILITY_FUNCTIONS_H

namespace cpp::utility {
	using namespace std;

	/// @brief 定义函数, 用于判断参数是否为只读引用
	///
	/// @tparam T 参数类型
	/// @param 参数
	template <typename T>
	void only_const_reference(const T&) {}

	/// @brief 重载 `only_const_reference` 函数, 当参数非只读引用时引发编译错误
	///
	/// @tparam T 参数类型
	/// @param 参数
	template <typename T>
	void only_const_reference(T&) { static_assert(false, "need const reference"); }
} // ! namespace cpp::utility

#endif // ! __CPLUSPLUS_UTILITY_FUNCTIONS_H
