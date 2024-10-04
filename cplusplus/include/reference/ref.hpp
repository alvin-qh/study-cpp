#pragma once

#ifndef __CPLUSPLUS_REFERENCE_REF_H
#define __CPLUSPLUS_REFERENCE_REF_H

namespace cpp {
	/// @brief 交换两个变量值
	///
	/// @tparam T 被交换值的类型
	/// @param a 被交换的两个值
	/// @param b 被交换的两个值
	template<typename T>
	inline void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
} // ! namespace cpp

#endif // ! __CPLUSPLUS_REFERENCE_REF_H
