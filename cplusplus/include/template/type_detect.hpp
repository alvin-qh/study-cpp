#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
#define __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H

namespace cpp {
	using namespace std;

	/// @brief 定义
	/// @tparam ...T
	template<typename...T>
	struct make_void {
		using type = void;
	};

	/// @brief 定义 `void_t` 类型
	/// @tparam ...T 任意模板参数列表
	template<typename...T>
	using void_t = typename make_void<T...>::type;

	template<typename T, typename = void>
	struct has_operator_sub : false_type {};

	/// @brief
	///
	/// 通过 `std::declval<T>` 模板函数可以在不产生 `T` 类型实例的情况下, 得到 `T` 类型的一个引用,
	/// 从而可以调用 `T` 类型的方法 (例如 `operator-`);
	///
	/// 而调用 `T` 类型方法时的参数, 也需要通过 `std::declval` 模板函数来产生,
	/// 从而在编译器完成函数整个签名的处理
	///
	/// `decltype` 关键字可以进行类型推导, 本例中 `decltype` 的参数为 `T` 类型的方法,
	/// 故推导出的类型为该方法的 "返回值"
	///
	/// 所以, `has_operator_sub` 模板类型的整体作用为
	///
	/// @tparam T
	template<typename T>
	struct has_operator_sub<T, void_t<decltype(declval<T>().operator-(declval<T&>()))>> : true_type {};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
