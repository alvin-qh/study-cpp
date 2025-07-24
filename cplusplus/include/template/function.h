#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__FUNC_H
#define __CPLUSPLUS_TEMPLATE__FUNC_H

#include <string>

namespace cxx::templated {
	using namespace std;

	/// @brief 使用 `NumberType` 定义泛型参数, 只接收数值类型参数
	///
	/// @tparam T 任意类型
	/// @param a 被加数
	/// @param b 加数
	/// @return 返回和
	template<typename T>
	T add(const T& a, const T& b) { return a + b; }

	/// @brief 定义 `add` 函数的特化版本
	///
	/// 当 `add` 函数的模板参数 `T` 为 `string` 类型时, 编译器会使用该特化版本
	///
	/// @param a 字符串 1
	/// @param b 字符串 2
	/// @return 字符串相加的结果
	template<>
	string add(const string& a, const string& b) {
		static const string sp(" ");
		return a + sp + b;
	}

	// -------------------------------------------------------------------------

#if __ge_cxx20
	/// @brief 定义模板约束, 表示改模板参数必须具备 `+` 运算符
	///
	/// @tparam T 待检测类型
	template<typename T>
	concept addition_type = requires(T n) {
		{ n + n } -> std::same_as<T>;
	};
#endif

	/// @brief 定义仿函数类型
	///
	/// 所谓的仿函数, 即一个重载了 `()` 运算符的类型
	///
	/// @tparam T 数值类型泛型参数
#if __ge_cxx20
	template <addition_type T>
	class AffineFunc {
#else
	template <typename T, typename = void>
	class AffineFunc;

	template <typename T>
	class AffineFunc<T, typename std::enable_if_t<std::is_arithmetic<T>::value>> {
#endif
	public:
		/// @brief 构造函数
		///
		/// @param x 输入值
		AffineFunc(T x) : _x(x) { }

		/// @brief 拷贝构造器
		///
		/// @param o 输入对象
		AffineFunc(const AffineFunc& o) = default;

		/// @brief 重载赋值运算符
		///
		/// @param o 输入对象
		/// @return 当前对象引用
		AffineFunc& operator=(const AffineFunc& o) = default;

		/// @brief 重载 `()` 运算符
		///
		/// @param y 输入值
		/// @return 参数 `y` 和当前值相加的结果
		T operator()(T y) const { return _x + y; }

		/// @brief 重载 `()` 运算符
		///
		/// @param y 输入值 1
		/// @param z 输入值 2
		/// @return 参数 `y` 和 `z` 与当前值相加的结果
		T operator()(T y, T z) const { return _x + y + z; }

		/// @brief 获取当前值
		///
		/// @return 当前值
		T value() const { return _x; }

	private:
		T _x;
	};

	} // namespace cxx::templated

#endif // __CPLUSPLUS_TEMPLATE__FUNC_H
