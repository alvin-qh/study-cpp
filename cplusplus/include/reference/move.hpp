#pragma once

#ifndef __CPLUSPLUS_REFERENCE_MOVE_H
#define __CPLUSPLUS_REFERENCE_MOVE_H

namespace cpp {
	using namespace std;

	/// @brief 将函数的参数返回
	///
	/// 该函数的参数为 `T` 类型引用, 在返回时, 会有如下不同情况:
	///
	/// 1. 如果使用 `T` 类型变量接收返回值, 则该函数返回的是 "左值"
	///    (即赋值运算符左边的值), 故会调用 `T` 类型的 "拷贝构造器"
	///    产生 "右值": `int num = return_some_one(10)`;
	///
	/// 2. 如果使用 `T&&` 类型变量接收返回值, 则该函数返回的是 "右值",
	///    即相当于将返回值 "移动" 到赋值运算符右边, 左边的值随即失效;
	///
	/// 所以, 作为右值的值必须是一个 "临时" 对象.
	///
	/// @tparam T
	/// @param val 参数值
	/// @return 返回参数值本身
	template <typename T>
	T return_some_one(const T& val) {
		return val;
	}

	class Moveable {
		typedef Moveable Self;
	private:
		int _x, _y, _z;
	public:
		Moveable()
			: _x(0)
			, _y(0)
			, _z(0) {
		}

		Moveable(int x, int y, int z)
			: _x(x)
			, _y(y)
			, _z(z) {
		}

		Moveable(const Self&& o) noexcept
			: _x(o._x)
			, _y(o._y)
			, _z(o._z) {
		}

		Moveable(const Self& o)
			: _x(o._x)
			, _y(o._y)
			, _z(o._z) {
		}

		Self& operator=(const Self&& o) noexcept {
			_x = o._x;
			_y = o._y;
			_z = o._z;
			return *this;
		}

		Self& operator=(const Self& o) {
			_x = o._x;
			_y = o._y;
			_z = o._z;
			return *this;
		};

		int x() const { return _x; }
		int y() const { return _y; }
		int z() const { return _z; }
	};

} // ! namespace cpp

#endif // ! __CPLUSPLUS_REFERENCE_MOVE_H
