#pragma once

#ifndef __CPLUSPLUS_OOP_AFFINE_FUNC_H
#define __CPLUSPLUS_OOP_AFFINE_FUNC_H

#include <type_traits>

namespace cpp {
	using namespace std;

	/// @brief 检测指定类型是否有 `+` 运算符
	/// @tparam T 待检测类型
	template<typename T, typename = void>
	struct has_operator_add : std::false_type {};

	template<typename T>
	struct has_operator_add<T, std::void_t<decltype(std::declval<T>() + std::declval<const T&>())>> : std::true_type {};

	/// 定义
	template<typename T>
	concept addition_type = has_operator_add<T>::value;

	// 定义数值类型
	// template<typename T>
	// concept arithmetic_type = is_arithmetic<T>::value;

	/// @brief 定义仿函数类型
	///
	/// 所谓的仿函数, 即一个重载了 `()` 运算符的类型
	///
	/// @tparam T 数值类型泛型参数
	template<addition_type T>
	class Addition {
	private:
		T _x;

	public:
		/// @brief 构造函数
		///
		/// @param x 输入值
		Addition(T x) :
			_x(x) {}

		/// @brief 拷贝构造器
		///
		/// @param o 输入对象
		Addition(const Addition& o) = default;

		/// @brief 重载赋值运算符
		///
		/// @param o 输入对象
		/// @return 当前对象引用
		Addition& operator=(const Addition& o) = default;

		/// @brief 重载 `()` 运算符
		///
		/// @param y 输入值
		/// @return 参数 `y` 和当前值相加的结果
		T operator()(T y) const {
			return _x + y;
		}

		/// @brief 重载 `()` 运算符
		///
		/// @param y 输入值 1
		/// @param z 输入值 2
		/// @return 参数 `y` 和 `z` 与当前值相加的结果
		T operator()(T y, T z) const {
			return _x + y + z;
		}

		/// @brief 获取当前值
		///
		/// @return 当前值
		T value() const {
			return _x;
		}
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_OOP_AFFINE_FUNC_H
