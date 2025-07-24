/// CTAD (Class template argument deduction) 是 C++ 17 增加的功能, 称为 C++ 类型推断指引
///
/// CATD 可以指定额外的模板类型推断规则, 或者修正现有的模板类型推断规则, 以满足复杂场景的模板类型推断
///
/// CATD 的推导原则为: 指定类构造器参数和其模板参数的对应关系, 从而在调用指定参数类型构造器时, 按照推断引导进行模板参数推导
#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__CTAD_H
#define __CPLUSPLUS_TEMPLATE__CTAD_H

#if __ge_cxx17

#include <string>

namespace cxx::templated {
	using namespace std;

	/// @brief 定义类测试模板类型推导指引
	///
	/// @tparam T 模板参数
	template <typename T1, typename T2>
	class CTAD {
	public:
		/// @brief 参数构造器
		///
		/// @param value 参数值的只读引用
		CTAD(const T1& v1, const T2& v2) : _v1(v1), _v2(v2) { }

		/// @brief 获取值对象的引用
		///
		/// @return 值对象引用
		T1& v1() { return _v1; }

		/// @brief 获取值对象的引用
		///
		/// @return 值对象引用
		T2& v2() { return _v2; }

		/// @brief 获取值对象的只读引用
		///
		/// @return 值对象的制度引用
		const T1& v1() const { return _v1; }

		/// @brief 获取值对象的只读引用
		///
		/// @return 值对象的制度引用
		const T2& v2() const { return _v2; }

		/// @brief 判断模板参数类型是否指定类型
		///
		/// @tparam U 待比较的指定类型
		/// @return `T` 和 `U` 是否相同类型
		template <typename U1, typename U2>
		constexpr bool is_same_type() const noexcept {
			return (std::is_same_v<T1, U1>) && (std::is_same_v<T2, U2>);
		}

	private:
		T1 _v1;
		T2 _v2;
	};

	// 当构造器参数为 `const char*` 时, 将模板 `T` 推到为 `std::string` 类型
	CTAD(const char*, const char*)->CTAD<string, string>;

	// 当构造器参数为 `int` 时, 将模板 `T` 推到为 `double` 类型
	CTAD(int, int)->CTAD<double, double>;

} // namespace cxx :templated

#endif // __ge_cxx17

#endif // __CPLUSPLUS_TEMPLATE__CTAD_H
