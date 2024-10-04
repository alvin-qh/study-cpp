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

	// --------------------------------------------------------------------------

	/// @brief 用于判断两个类型是否相同
	///
	/// 如果模板传入了两个类型, 则 `is_same_type` 类型继承自 `std::false_type`
	///
	/// @tparam T1 类型 1
	/// @tparam T2 类型 2
	template<typename T1, typename T2>
	struct is_same_type : std::false_type {};

	/// @brief 对 `is_same_type` 类型进行特化, 令两个类型一致
	///
	/// 对 `is_same_type` 类型进行特化, 当两个泛型参数类型一致时, 令 `is_same_type`
	/// 类型继承自 `std::true_type`
	///
	/// @tparam T1 类型
	template<typename T1>
	struct is_same_type<T1, T1> : std::true_type {};

	/// @brief 检测
	/// @tparam T
	template<typename T>
	class is_default_constructible {
		template<typename U = T, typename = decltype(U())>
		static std::true_type test(void*) { return std::true_type(); }

		template<typename U>
		static std::false_type test(...) { return std::false_type(); }
	public:
		static constexpr bool value = is_same_type<decltype(test<T>(nullptr)), std::true_type>::value;
	};

	// --------------------------------------------------------------------------

	/// @brief 定义模板类型, 无论模板参数为何, 其 `make_void<T>::type` 都为 `void` 类型
	///
	/// @tparam ...T 任意模板参数
	template<typename...T>
	struct make_void {
		using type = void;
	};

	/// @brief 定义 `void_t` 类型
	///
	/// @tparam ...T 任意模板参数列表
	template<typename...T>
	using void_t = typename make_void<T...>::type;

	/// @brief 用于检测指定类型是否包含 `T operator-(const T&)` 方法
	///
	/// C++ 20 版本之前, 没有提供直接检测类型方法的办法, 但可以使用 C++ 的模板特性间接达成目标;
	///
	/// `has_operator_sub` 类型的基本原理是:
	///
	/// 1. `has_operator_sub` 类型具备两个模板参数, 默认继承自 `std::false_type`,
	///    其中 `T` 参数表示要检测的目标类型;
	///
	/// 2. 对 `has_operator_sub` 进行偏特化, 令其第二个模板参数为
	///    `void_t<decltype(declval<T>().operator-(declval<const T&>()))>` 类型,
	///    如果第二个模板参数偏特化成功, 则 `has_operator_sub` 将继承自 `std::true_type`
	///
	/// 整体借助了 C++ 的 SFINAE 特性, 即所给类型导致模板参数无效时, 不会立即编译失败,
	/// 而是尝试模板参数的其它展开方式
	///
	/// `std::declval` 函数用于获取所给类型的 "右值引用" 而无需对类型进行实例化, 故:
	/// `declval<T>().operator-(declval<const T&>())` 表示 `T::operator-(const T&)`
	/// 方法的引用;
	///
	/// 接下来, 即通过 `decltype` 关键字对方法引用进行类型推断, 获得 `T::operator-(const T&)`
	/// 方法返回值类型;
	///
	/// 也就是说, 只要 `T` 类型具备 `T::operator-(const T&)` 方法, `has_operator_sub`
	/// 类型的偏特化会成立, 从而 `has_operator_sub<T>` 继承自 `std::true_type` 类型,
	/// 否则会继承自 `std::false_type` 类型, 从而完成 `T` 类型是否包含 `T::operator-(const T&)`
	/// 方法的检测
	///
	/// @tparam T 待检测类型
	template<typename T, typename = void>
	struct has_operator_sub : std::false_type {};

	/// @brief `has_operator_sub` 类型的偏特化定义
	///
	/// @tparam T 待检测类型
	template<typename T>
	struct has_operator_sub<T, void_t<decltype(std::declval<T>().operator-(std::declval<const T&>()))>> : std::true_type {};
} // namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_SFINAE_H
