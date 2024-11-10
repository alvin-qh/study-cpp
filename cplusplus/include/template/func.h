#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__FUNC_H
#define __CPLUSPLUS_TEMPLATE__FUNC_H

#include <string>

namespace cxx::templated {
	using namespace std;

	/// @brief 使用 `NumberType` 定义泛型参数, 只接收数值类型参数
	///
	/// @tparam T 任意类型
	/// @param a 被加数
	/// @param b 加数
	/// @return 返回和
	template<typename T>
	T add(const T& a, const T& b) { return a + b; }

	/// @brief 定义 `add` 函数的特化版本
	///
	/// 当 `add` 函数的模板参数 `T` 为 `string` 类型时, 编译器会使用该特化版本
	///
	/// @param a 字符串 1
	/// @param b 字符串 2
	/// @return 字符串相加的结果
	template<>
	string add(const string& a, const string& b) {
		static const string sp(" ");
		return a + sp + b;
	}

} // namespace cxx::templated

#endif // __CPLUSPLUS_TEMPLATE__FUNC_H
