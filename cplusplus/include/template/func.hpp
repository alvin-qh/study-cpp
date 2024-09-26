#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_FUNC_H
#define __CPLUSPLUS_TEMPLATE_FUNC_H

#include <type_traits>

namespace cpp {
	/**
	 * 定义
	 */
	template<typename T>
	T add(T a, T b) {
		return a + b;
	}
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_FUNC_H
