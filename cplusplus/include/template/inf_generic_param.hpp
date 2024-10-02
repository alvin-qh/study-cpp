#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_INF_GENERIC_PARAM_H
#define __CPLUSPLUS_TEMPLATE_INF_GENERIC_PARAM_H

namespace cpp {
	/// @brief 通过可变模板参数定义的参数列表调用回调函数
	///
	/// 通过可变参数模板 `...Args` 定义函数参数 `args`,
	/// 可以将其展开 (`args...`) 后, 作为被调用函数的参数列表
	///
	/// @tparam R 返回值类型
	/// @tparam Fn 回调函数类型
	/// @tparam ...Args 回调函数参数类型 (可变模板参数)
	/// @param fn 回调函数实例
	/// @param ...args 根据可变模版参数定义的函数参数列表
	/// @return 回调函数返回值
	template<typename R, typename Fn, typename ...Args>
	R callback(Fn fn, Args...args) {
		return fn(args...);
	}

	/// @brief 递归停止函数
	///
	/// 当 `recursive_args` 模板函数的 `Args` 可变模板参数递归到数量为 `1` 时,
	/// 会调用该函数表示递归结束 (最后一个模板参数对应到 `T`)
	///
	/// @tparam T 最后一个模板参数
	/// @param head 最后一个参数, 类型对应模板参数 `T`
	/// @return 返回 `head` 参数
	template<typename T>
	T recursive_args(T head) {
		return head;
	}

	/// @brief 通过递归方式使用可变模板参数
	///
	/// @tparam T 第一个模板参数
	/// @tparam ...Args 可变模板参数
	/// @param head 第一个参数, 类型对应模板参数 `T`
	/// @param ...args 展开的模板参数, 类型逐一对应模板参数 `Args`
	/// @return 计算结果
	template<typename T, typename ...Args>
	T recursive_args(T head, Args...args) {
		return head + recursive_args<T>(args...);
	}
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_INF_GENERIC_PARAM_H
