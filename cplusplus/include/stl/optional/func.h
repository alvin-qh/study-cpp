#pragma once

#ifndef __CPLUSPLUS_STL_OPTIONAL__OPTIONAL_H
#define __CPLUSPLUS_STL_OPTIONAL__OPTIONAL_H

#if __ge_cxx17

#include <optional>

namespace cxx::stl {
	using namespace std;

	/// @brief 通过函数返回值返回 `std:optional` 类型对象
	///
	/// 当函数返回值为 `std::optional<T>` 时, 在函数中返回 `T` 类型值,
	/// 即可自动包装为 `std::optional<T>` 类型对象
	///
	/// @param n 整数值
	/// @return `optional<int>` 类对象
	optional<int> check_even_number(int n);

} // namespace cxx::std

#endif // __ge_cxx17

#endif // __CPLUSPLUS_STL_OPTIONAL__OPTIONAL_H
