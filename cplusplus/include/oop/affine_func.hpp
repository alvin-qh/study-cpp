#pragma once

#ifndef __CPLUSPLUS_AFFINE_FUNC_H
#define __CPLUSPLUS_AFFINE_FUNC_H

#include <stdint.h>
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
		Addition(T x)
			: _x(x) {}

		T operator()(T y) const {
			return _x + y;
		}

		T operator()(T y, T z) const {
			return _x + y + z;
		}

		T value() const {
			return _x;
		}
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_AFFINE_FUNC_H
