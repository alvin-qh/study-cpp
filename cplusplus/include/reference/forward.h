#pragma once

#ifndef __CPLUSPLUS_REFERENCE__FORWARD_H
#define __CPLUSPLUS_REFERENCE__FORWARD_H

#include <utility>

namespace cxx::reference {

	/// @brief 定义
	enum ARGUMENT_TYPE {
		LEFT_REF,
		RIGHT_REF,
	};

	/// @brief 用于检测引用类型的函数
	///
	/// @tparam T 对象类型
	/// @return `ARGUMENT_TYPE` 类型枚举
	template <typename T>
	constexpr ARGUMENT_TYPE __what_kind_of_ref(T&) { return LEFT_REF; }

	template <typename T>
	constexpr ARGUMENT_TYPE __what_kind_of_ref(T&&) { return RIGHT_REF; }

	/// @brief 通过 `forward` 函数, 将 `ref` 参数进行转发, 传递给下游函数
	///
	/// 对于 `T&&` 引用类型参数, 在 C++ 中可以通过所谓的 "引用折叠" 规则,
	/// 在不同情况下表达为左值引用或右值引用:
	///
	/// - 当为 `ref` 传递变量时, 相当于传递变量的引用, 即 `&` 引用, 则
	///  `ref` 参数类型为 `T&& &`, 折叠后为 `T&`;
	///
	/// - 当为 `ref` 传递右值引用时, 相对于传递 `&&` 引用, 则 `ref`
	///  参数类型为 `T&& &&`, 折叠后为 `T&&`;
	///
	/// 简言之, 将函数参数定义为 `T&& ref` 表示, `ref` 既可以是一个左值引用,
	/// 也可以是一个右值引用, 这一点和类的 "移动拷贝构造器" 以及 "移动赋值操作符"
	/// 是不同概念
	///
	/// 注意, 函数 `template <typename T> ARGUMENT_TYPE do_forward(T& ref)`
	/// 与当前函数不是重载关系, 而是同一个函数定义, 故无法进行同时定义
	///
	/// `std::forward` 称为 "完美转发", 即 "保留参数原始引用类型" 的转发, 简言之,
	/// `std::forward` 会将左值引用参数转为左值引用, 右值引用参数转为右值引用,
	/// 不会改变参数原本的引用情况
	///
	/// @tparam T 参数类型
	/// @param ref 指定参数类型的引用
	/// @return 参数的引用类型
	template <typename T>
	ARGUMENT_TYPE do_forward(T&& ref) { return __what_kind_of_ref(std::forward<T>(ref)); }

} // namespace cxx::reference

#endif // __CPLUSPLUS_REFERENCE__FORWARD_H
