#pragma once

#ifndef __CPLUSPLUS_OOP_AFFINE_FUNC_H
#define __CPLUSPLUS_OOP_AFFINE_FUNC_H

#include <type_traits>

using namespace std;

namespace cpp {
	/// 定义数值类型泛型参数
	template<typename T>
	concept NumberType = is_arithmetic<T>::value;

	/// @brief 定义仿函数类型
	///
	/// 所谓的仿函数, 即一个重载了 `()` 运算符的类型
	///
	/// @tparam T
	template<NumberType T>
	class Addition {
	private:
		T _x;

	public:
		/// @brief 构造函数
		///
		/// @param x 输入值
		Addition(T x)
			: _x(x) {}

		Addition(const Addition& o)
			: _x(o._x) {}

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
