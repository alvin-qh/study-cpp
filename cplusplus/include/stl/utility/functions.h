#pragma once

#ifndef __CPLUSPLUS_STL_UTILITY__FUNCTIONS_H
#define __CPLUSPLUS_STL_UTILITY__FUNCTIONS_H

namespace cxx::stl {

	using namespace std;

	/// @brief 定义函数, 用于判断参数是否为只读引用
	///
	/// @tparam T 参数类型
	/// @param 参数
	template <typename T>
	inline constexpr void only_const_reference(const T&) { }

	/// @brief 重载 `only_const_reference` 函数, 当参数非只读引用时引发编译错误
	///
	/// @tparam T 参数类型
	/// @param 参数
	template <typename T>
	inline constexpr void only_const_reference(T&) = delete;

} // namespace cxx::utility

#endif // __CPLUSPLUS_STD_UTILITY__FUNCTIONS_H
