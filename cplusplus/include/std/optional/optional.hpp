#pragma once

#ifndef __CPLUSPLUS_STD_OPTIONAL_H
#define __CPLUSPLUS_STD_OPTIONAL_H

#include <optional>

namespace cpp::std_ {
	using namespace std;

	/// @brief 通过函数返回值返回 `std:optional` 类型对象
	///
	/// 当函数返回值为 `std::optional<T>` 时, 在函数中返回 `T` 类型值,
	/// 即可自动包装为 `std::optional<T>` 类型对象
	///
	/// @param n 整数值
	/// @return `optional<int>` 类对象
	optional<int> check_even_number(int n) {
		if (n % 2 == 0) {
			return n;
		}
		return std::nullopt;
	}

} // ! namespace cpp::std

#endif // ! __CPLUSPLUS_STD_OPTIONAL_H
