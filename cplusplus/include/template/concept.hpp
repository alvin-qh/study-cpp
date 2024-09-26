#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_CONCEPT_H
#define __CPLUSPLUS_TEMPLATE_CONCEPT_H

#include <type_traits>

namespace cpp {
	// 定义数值类型泛型参数
	template<typename T>
	concept NumberType = std::is_arithmetic<T>::value;

	/**
	 * 使用 `NumberType` 定义泛型参数, 只接收数值类型参数
	 */
	template<NumberType T>
	T add(T a, T b) {
		return a + b;
	}
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_CONCEPT_H
