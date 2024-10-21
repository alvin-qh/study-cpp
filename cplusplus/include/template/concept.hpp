#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_CONCEPT_H
#define __CPLUSPLUS_TEMPLATE_CONCEPT_H

#include <type_traits>
#include <concepts>

namespace cpp::temp {

	/// @brief 通过 `concept` 关键字声明符合特定要求的模板定义
	///
	/// ```
	/// template<typename T>
	/// concept [name] = [true/false];
	/// ```
	///
	/// 需要 C++ 20 以上版本
	template<typename T>
	concept number_only_type = std::is_arithmetic<T>::value;

	/// @brief 使用 `number_only_type` 定义泛型参数, 只接收数值类型参数
	///
	/// @tparam T `number_only_type` 定义的泛型参数, 只能为数值类型
	/// @param a 被加数
	/// @param b 加数
	/// @return 返回和
	template <number_only_type T>
	// template<typename T> requires number_only_type<T>
	T add(T a, T b) { return a + b; }

	// --------------------------------------------------------------------------

	/// @brief 用于判断模板参数 `T` 是否具备 `-` 运算符的模板类型
	template<typename T, typename = void>
	struct has_operator_sub : std::false_type {};

	template<typename T>
	struct has_operator_sub<T, std::void_t<decltype(std::declval<T>() - std::declval<const T&>())>> : std::true_type {};

	/// @brief 通过 `requires` 关键字约束模板类型
	///
	/// ```
	/// template<typename T>
	/// 	requires [true/false]
	/// class SomeClass { ... }
	/// ```
	///
	/// @tparam T 模板参数
	template<typename T>
		requires (std::is_arithmetic<T>::value) && (has_operator_sub<T>::value)
	struct Subtract {
		static T sub(T a, T b) { return a - b; }
	};

	// --------------------------------------------------------------------------

	template<typename T>
	concept has_operator_multiply =
		std::is_arithmetic<T>::value &&
		requires(T a, T b) { a* b; };

	template <typename T> requires has_operator_multiply<T>
	// template <has_operator_multiply T>
	T multiply(T a, T b) { return a * b; }

	// --------------------------------------------------------------------------

	template<typename T>
	concept self_addition =
		std::is_arithmetic<T>::value &&
		requires(T n) {
			{ ++n } -> std::same_as<T&>;
			{ n++ } -> std::same_as<T>;
	};

	template <self_addition T>
	T& increment(T& n) { return ++n; }

} // ! namespace cpp::temp

#endif // ! __CPLUSPLUS_TEMPLATE_CONCEPT_H
