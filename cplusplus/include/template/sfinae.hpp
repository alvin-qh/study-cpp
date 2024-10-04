/// SFINAE 指的是 C++ 的一种模板编译策略
///
/// SFINAE (Substitution failure is not an error), 指的是:
/// 在模板形参替换实参的编译过程中, 如果参数不匹配, 编译器不会直接报错,
/// 而是继续尝试其它的可能, 直到所有的模板展开都无法匹配模板定义,
/// 才会最终报告编译错误 (SFINAE error)
///
/// SFINAE 特性使 C++ 支持了模板参数重载以及模板类型的特化、偏特化能力
#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_SFINAE_H
#define __CPLUSPLUS_TEMPLATE_SFINAE_H

namespace cpp {
	/// @brief 当 `T` 类型内部具备 `T::type_x` 类型时, `foo` 模板函数的特化
	///
	/// @tparam T 具备 `T::type_x` 类型定义的类型
	template <typename T>
	const char* foo(typename T::type_x) {
		return "foo-type-x";
	}

	/// @brief 当 `T` 类型内部具备 `T::type_y` 类型时, `foo` 模板函数的特化
	///
	/// @tparam T 具备 `T::type_y` 类型定义的类型
	template <typename T>
	const char* foo(typename T::type_y) {
		return "foo-type-y";
	}

	/// @brief 当 `foo` 函数的所有特化都不满足时, 编译器选择 `foo` 函数
	template <typename T>
	const char* foo(T) {
		return "foo-type-any";
	}

	/// @brief 用于判断两个类型是否相同
	///
	/// 如果模板传入了两个类型, 则模板继承自 `std::false_type`
	///
	/// @tparam T1 类型 1
	/// @tparam T2 类型 2
	template<typename T1, typename T2>
	struct is_same_type : std::false_type {};

	/// @brief 对 `is_same_type` 类型进行特化, 令两个类型一致
	///
	/// `is_same_type` 
	///
	/// @tparam T1 类型
	template<typename T1>
	struct is_same_type<T1, T1> : std::true_type {};

	template<typename T>
	class is_default_constructible {
		template<typename U = T, typename = decltype(U())>
		static std::true_type test(void*) { return std::true_type(); }

		template<typename U>
		static std::false_type test(...) { return std::false_type(); }

	public:
		static constexpr bool value = is_same_type<decltype(test<T>(nullptr)), std::true_type>::value;
	};
} // namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_SFINAE_H
