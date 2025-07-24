/// C++ 20 版本为模板增加了 "概念" (`concept`) 特性, 用于更精确的模板类型推导和模板类型约束
#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__CONCEPT_H
#define __CPLUSPLUS_TEMPLATE__CONCEPT_H

#if __ge_cxx20

#include <type_traits>
#include <concepts>

namespace cxx::templated {

	/// @brief 通过 `concept` 关键字声明符合特定要求的模板定义
	///
	/// `concept` 关键字后为布尔常量表达式, 如果常量表达式的值为 `true`, 则表示模板参数 `T`
	/// 有效, 反之表示模板参数 `T` 无效
	///
	/// 需要 C++ 20 以上版本
	template<typename T>
	concept numeric_type_v1 = std::is_arithmetic<T>::value;

	/// @brief 使用 `numeric_type_v1` 定义泛型参数, 只接收数值类型参数
	///
	/// `concept numeric_type_v1 = ...` 用法 1: 使用定义的 `numeric_type_v1`
	/// 名称替换 `typename` 关键字
	///
	/// @tparam T 通过 `numeric_type_v1` 定义的模板参数, 只能为数值类型
	template <numeric_type_v1 T>
	T add1(T a, T b) { return a + b; }

	/// @brief 使用 `numeric_type_v1` 约束泛型参数, 只接收数值类型参数
	///
	/// `concept numeric_type_v1 = ...` 用法 2: 通过 `requires` 关键字约束模板参数
	///
	/// @tparam T 被 `numeric_type_v1` 约束的模板参数, 只能为数值类型
	template <typename T>
		requires numeric_type_v1<T>
	T add2(T a, T b) { return a + b; }

	// --------------------------------------------------------------------------

	/// @brief 用于判断模板参数 `T` 是否具备减法运算的模板类型
	template<typename T, typename = void>
	struct has_add_operator : std::false_type { };

	template<typename T>
	struct has_add_operator<T, std::void_t<decltype(std::declval<T>() + std::declval<const T&>())>> : std::true_type { };

	/// @brief `concept` 关键字后的表达式支持逻辑运算, 包括 `&&`, `||`, `!` 运算
	///
	/// 本例中通过逻辑表达式, 约束 `T` 模板参数的约束条件为: 1. 数值类型; 2. 具备减号运算符;
	template <typename T>
	concept can_add_type_v1 =
		std::is_arithmetic<T>::value &&
		has_add_operator<T>::value;

	// --------------------------------------------------------------------------

	/// @brief 通过 `requires` 关键字, 配合 `concept` 定义约束模板类型
	///
	/// 也可以将 `typename` 关键字替换为 `can_add_type_v1` 达到相同效果
	///
	/// @tparam T 受 `requires` 关键字约束的模板参数
	template <typename T>
		requires can_add_type_v1<T>
	T add3(T a, T b) { return a + b; }

	// --------------------------------------------------------------------------

	/// @brief 通过 `requires` 关键字约束模板类型
	///
	/// `requires` 关键字后为 `bool` 类型的常量表达式, 如果表达式的值为 `true`,
	/// 则模板参数 `T` 生效, 否则报告编译错误
	///
	/// 本例中通过 `requires` 关键字约束了 `T` 模板参数的类型: 1. 数值类型; 2. 具备加法运算符;
	///
	/// @tparam T 受 `requires` 约束的模板参数
	template<typename T>
		requires (std::is_arithmetic<T>::value) && (has_add_operator<T>::value)
	T add4(T a, T b) { return a + b; }

	// --------------------------------------------------------------------------

	/// @brief 通过 `requires` 关键字为 `concept` 定义约束
	///
	/// 本例中, 通过 `requires` 关键字表示 "`T` 类型变量必须具备指定操作" 的约束
	template<typename T>
	concept can_add_type_v2 =
		std::is_arithmetic<T>::value &&
		requires(T a, T b) { a + b; };  // 两个 `T` 类型变量必须可以相加

	/// @brief 通过 `requires` 关键字, 将 `concept` 用于模板参数约束
	///
	/// @tparam T 被约束的模板参数
	template <typename T>
		requires can_add_type_v2<T>
	T add5(T a, T b) { return a + b; }

	// --------------------------------------------------------------------------

	/// @brief 通过 `requires` 关键字为 `concept` 定义约束
	///
	/// 本例中, 通过 `requires` 关键字表示 "`T` 类型变量的操作必须具备指定返回值" 的约束
	template<typename T>
	concept can_add_type_v3 =
		std::is_arithmetic<T>::value &&
		requires(T n) {
			{ ++n } -> std::same_as<T&>;  // `T` 类型变量需具备 `++` 运算符且能够返回 `T&` 类型结果
			{ n++ } -> std::same_as<T>;   // `T` 类型变量需具备 `++(int)` 运算符且能够返回 `T` 类型结果
	}&& requires(T a, T b) {
		{ a + b } -> std::same_as<T>;     // `T` 类型两个变量需能相加, 且能够返回 `T` 类型结果
		{ a += b } -> std::same_as<T&>;   // `T` 类型两个变量需能赋值相加, 且能够返回 `T&` 类型结果
	};

	template <can_add_type_v3 T>
	T add6(T a, T b) { return a + b; }

} // namespace cxx::templated

#endif // __ge_cxx20
#endif // __CPLUSPLUS_TEMPLATE__CONCEPT_H
