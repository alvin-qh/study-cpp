#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_CONCEPT_H
#define __CPLUSPLUS_TEMPLATE_CONCEPT_H

namespace cpp {
	using namespace std;

	/// 定义数值类型泛型参数
	template<typename T>
	concept NumberType = is_arithmetic<T>::value;

	/// @brief 使用 `NumberType` 定义泛型参数, 只接收数值类型参数
	///
	/// @tparam T `NumberType` 类型泛型参数, 只能为数值类型
	/// @param a 被加数
	/// @param b 加数
	/// @return 返回和
	template<NumberType T>
	T add(T a, T b) {
		return a + b;
	}
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_CONCEPT_H
