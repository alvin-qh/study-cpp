/// SFINAE 指的是 C++ 的一种模板编译策略
///
/// SFINAE (Substitution failure is not an error), 指的是:
/// 在模板形参替换实参的编译过程中, 如果参数不匹配, 编译器不会直接报错,
/// 而是继续尝试其它的可能, 直到所有的模板展开都无法匹配模板定义,
/// 才会最终报告编译错误 (SFINAE error)
#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_SFINAE_H
#define __CPLUSPLUS_TEMPLATE_SFINAE_H

namespace cpp {
	/// @brief 定义类型, 内部包含 `type_x` 类型定义
	///
	/// `type_x` 类型为 `int` 类型的别名
	struct X {
		typedef int type_x;
	};

	/// @brief 定义类型, 内部包含 `type_y` 类型定义
	///
	/// `type_y` 类型为 `int` 类型的别名
	struct Y {
		typedef int type_y;
	};

	/// @brief 当 `T` 类型内部具备 `T::type_x` 类型时, `foo` 模板函数的特化
	///
	/// @tparam T 具备 `T::type_x` 类型定义的类型
	template <typename T> const char* foo(typename T::type_x) { return "foo-type-x"; }

	/// @brief 当 `T` 类型内部具备 `T::type_y` 类型时, `foo` 模板函数的特化
	///
	/// @tparam T 具备 `T::type_y` 类型定义的类型
	template <typename T> const char* foo(typename T::type_y) { return "foo-type-y"; }

	/// @brief 当 `foo` 函数的所有特化都不满足时, 编译器选择 `foo` 函数
	template <typename T> const char* foo(T) { return "foo-type-any"; }

	struct true_type {
		static constexpr bool value = true;
	};

	struct false_type {
		static constexpr bool value = false;
	};

	template<T>
	struct enable_if {
		typedef true_type type;
	};
}

#endif // ! __CPLUSPLUS_TEMPLATE_SFINAE_H
