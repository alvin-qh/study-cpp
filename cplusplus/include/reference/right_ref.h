#pragma once

#ifndef __CPLUSPLUS_REFERENCE__RIGHT_REF_H
#define __CPLUSPLUS_REFERENCE__RIGHT_REF_H

#include <type_traits>

namespace cxx::reference {

	/// @brief 检测一个变量是否 "右值引用" 类型
	///
	/// @tparam T 变量类型
	template<typename T>
	struct is_right_reference {
		/// @brief 判断变量类型是否为右值引用
		///
		/// @param 右值引用类型参数
		/// @return 返回常量 `true`
		static constexpr bool test(T&&) { return true; }

		/// @brief 判断变量类型是否为右值引用
		///
		/// @param 左值可变引用类型参数
		/// @return 返回常量 `true`
		static constexpr bool test(T&) { return false; }

		/// @brief 判断变量类型是否为右值引用
		///
		/// @param 左值只读引用类型
		/// @return 返回常量 `true`
		static constexpr bool test(const T&) { return false; }
	};

} // namespace cxx::reference

#endif // __CPLUSPLUS_REFERENCE__RIGHT_REF_H
