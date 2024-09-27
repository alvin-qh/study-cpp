#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_FUNC_H
#define __CPLUSPLUS_TEMPLATE_FUNC_H

namespace cpp {
	/// @brief 使用 `NumberType` 定义泛型参数, 只接收数值类型参数
	///
	/// @tparam T 任意类型
	/// @param a 被加数
	/// @param b 加数
	/// @return 返回和
	template<typename T>
	T add(T a, T b) {
		return a + b;
	}
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_FUNC_H
