#pragma once

#ifndef __CPLUSPLUS_STL_VARIANT__OVERLOADED_H
#define __CPLUSPLUS_STL_VARIANT__OVERLOADED_H

namespace cxx::stl {

	/// @brief 定义重载函数类型
	///
	/// 该类型继承自一组函数类型 (多继承), 并将父类的 `operator()` 操作符引用到自身类型中,
	///
	/// 相当于 `overloaded` 类型中会产生一组重载的 `operator(...)` 运算符重载, 且每个
	/// `operator(...)` 操作符均从其模板定义的父类继承而来
	///
	/// 这里涉及到不定模板参数的语法规范以及不定模板展开规则
	///
	/// @tparam ...Ts 不定模板参数, 当前类从这些模板参数定义的类型继承
	template <typename... Ts>
	struct overloaded : Ts... {
		// 展开一组 `operator()` 运算符, 各运算符均从父类继承
		using Ts::operator()...;
	};

	// 指定模板推导指引, 当构造器参数为 `Ts...` 时, 模板参数为 `<Ts...>`
	template <typename... Ts>
	overloaded(Ts...) -> overloaded<Ts...>;

} // namespace cxx::stl

#endif // !__CPLUSPLUS_STL_VARIANT__OVERLOADED_H
