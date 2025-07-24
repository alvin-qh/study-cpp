/// 类型特化
///
/// C++ 允许对现有模板进行特化定义, 特化包括: "偏特化" 以及 "全特化"
///
/// 所谓 "偏特化", 指的是对现有模板类的部分模板参数进行固定;
/// 而所谓 "全特化" 指的是对现有模板类的全部模板参数进行固定;
///
/// "全特化" 是 "偏特化" 的一种特例;
///
/// 注意: 特化并不能改变模板参数的数量, 而是给类模板定义 "特例", 例如:
/// 对于原始模板类 `template <typename T1, typename T2> class A` 来说,
/// 模板类 `template <typename T> class A<T, int>`
/// 表示将原始模板类的 `T2` 模板参数固定为 `int` 类型, 故:
/// `A<double, char>` 将通过原始模板类实例化对象, 而 `A<double, int>`
/// 将通过偏特化类实例化对象
#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__SPECIALIZATION_H
#define __CPLUSPLUS_TEMPLATE__SPECIALIZATION_H

#include <string>
#include <fmt/core.h>

namespace cxx::templated {
	using namespace std;

	/// @brief 定义父类, 简化代码书写
	///
	/// @tparam T1 模板参数 1
	/// @tparam T2 模板参数 2
	template <typename T1, typename T2>
	class GeneralBase {
	protected:
		T1 _v1;
		T2 _v2;
	public:
		/// @brief 参数构造器
		GeneralBase(const T1& v1, const T2& v2) : _v1(v1), _v2(v2) { }

		/// @brief 析构函数
		virtual ~GeneralBase() = default;

		/// @brief 将对象转为字符串
		virtual string to_string() const = 0;
	};

	/// @brief 定义模板类
	///
	/// @tparam T1 模板参数 1
	/// @tparam T2 模板参数 2
	template <typename T1, typename T2>
	class Special : public GeneralBase<T1, T2> {
		typedef GeneralBase<T1, T2> _base;
	public:
		/// @brief 参数构造器
		Special(const T1& v1, const T2& v2) : _base(v1, v2) { }

		/// @brief 析构函数
		virtual ~Special() = default;

		/// @brief 将对象转为字符串
		virtual string to_string() const override {
			return fmt::format("Special<T1, T2>({0}, {1})", this->_v1, this->_v2);
		}
	};

	/// @brief 定义 `Special<T1, T2>` 模板类的偏特化模板类
	///
	/// 本次偏特化, 将 `Special<T1, T2>` 模板类的 `T2` 模板参数固定为 `string` 类型
	///
	/// 当通过 `Special<X, string>(..., "any string");` (`X` 为任意类型)
	/// 的形式实例化对象时, C++ 编译器会选择当前偏特化类作为对象类型
	///
	/// @tparam T 模板参数
	template <typename T>
	class Special<T, string> : public GeneralBase<T, string> {
		typedef GeneralBase<T, string> _base;
	public:
		/// @brief 参数构造器
		Special(const T& v1, const string& v2) : _base(v1, v2) { }

		/// @brief 析构函数
		virtual ~Special() = default;

		/// @brief 将对象转为字符串
		virtual string to_string() const override {
			return fmt::format("Special<T, string>({0}, {1})", this->_v1, this->_v2);
		}
	};

	/// @brief 定义 `Special<T1, T2>` 模板类的偏特化模板类
	///
	/// 本次偏特化, 将 `Special<T1, T2>` 模板类的 `T1`, `T2` 模板参数固定为 `T` 类型
	///
	/// 当通过 `Special<X, X>(..., ...);` (`X` 为任意类型) 的形式实例化对象时,
	/// C++ 编译器会选择当前偏特化类作为对象类型
	///
	/// @tparam T 模板参数
	template <typename T>
	class Special<T, T> : public GeneralBase<T, T> {
		typedef GeneralBase<T, T> _base;
	public:
		/// @brief 参数构造器
		Special(const T& v1, const T& v2) : _base(v1, v2) { }

		/// @brief 析构函数
		virtual ~Special() = default;

		/// @brief 将对象转为字符串
		virtual string to_string() const override {
			return fmt::format("Special<T, T>({0}, {1})", this->_v1, this->_v2);
		}

		/// @brief 该函数只在 `Special<T, T>` 特化类型下有效
		constexpr bool same_generic_args() const { return true; }
	};

	/// @brief 定义 `Special<T1, T2>` 模板类的偏特化模板类
	///
	/// 本次偏特化, 将 `Special<T1, T2>` 模板类的 `T1`, `T2` 模板参数固定为 `string` 类型
	///
	/// 当通过 `Special<string, string>("any string", "any string");` 的形式实例化对象时,
	/// C++ 编译器会选择当前偏特化类作为对象类型
	///
	/// @tparam T 模板参数
	template<>
	class Special<string, string> : public GeneralBase<string, string> {
		typedef GeneralBase<string, string> _base;
	public:
		/// @brief 参数构造器
		Special(const string& v1, const string& v2) : _base(v1, v2) { }

		/// @brief 析构函数
		virtual ~Special() = default;

		/// @brief 将对象转为字符串
		virtual string to_string() const override {
			return fmt::format("Special<string, string>({0}, {1})", this->_v1, this->_v2);
		}

		/// @brief 该函数只在 `Special<string, string>` 特化类型下有效
		string concat(const string& splitter) const { return this->_v1 + splitter + this->_v2; }
	};

	/// @brief 定义 `Special<T1, T2>` 模板类的偏特化模板类
	///
	/// 本次偏特化, 将 `Special<T1, T2>` 模板类的 `T1`, `T2` 模板参数固定为 `string` 类型
	///
	/// 当通过 `Special<string, string>("any string", "any string");` 的形式实例化对象时,
	/// C++ 编译器会选择当前偏特化类作为对象类型
	///
	/// @tparam T 模板参数
	template<typename T1, typename T2>
	class Special<T1*, T2*> : public GeneralBase<T1*, T2*> {
		typedef GeneralBase<T1*, T2*> _base;
	public:
		/// @brief 参数构造器
		Special(T1* const& v1, T2* const& v2) : _base(v1, v2) { }

		/// @brief 析构函数
		virtual ~Special() = default;

		/// @brief 将对象转为字符串
		virtual string to_string() const override {
			return fmt::format("Special<T1*, T2*>({0}, {1})", *this->_v1, *this->_v2);
		}
	};

} // namespace cxx::templated

#endif // __CPLUSPLUS_TEMPLATE__SPECIALIZATION_H
