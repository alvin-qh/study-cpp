#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
#define __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H

namespace cpp {
	using namespace std;

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
	struct has_operator_sub : false_type {};

	/// @brief `has_operator_sub` 类型的偏特化定义
	///
	/// @tparam T 待检测类型
	template<typename T>
	struct has_operator_sub<T, void_t<decltype(declval<T>().operator-(declval<const T&>()))>> : true_type {};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
