/// SFINAE 指的是 C++ 的一种模板编译策略
///
/// SFINAE (Substitution failure is not an error), 指的是:
/// 在模板形参替换实参的编译过程中, 如果参数不匹配, 编译器不会直接报错,
/// 而是继续尝试其它的可能, 直到所有的模板展开都无法匹配模板定义,
/// 才会最终报告编译错误 (SFINAE error)
///
/// SFINAE 特性使 C++ 支持了模板参数重载以及模板类型的特化、偏特化能力
#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__SFINAE_H
#define __CPLUSPLUS_TEMPLATE__SFINAE_H

#include <type_traits>
#include <utility>

namespace cxx::templated {

	/// @brief 当 `T` 类型内部具备 `T::type_x` 类型时, `foo` 模板函数的特化
	///
	/// @tparam T 具备 `T::type_x` 类型定义的类型
	template <typename T>
	const char* foo(typename T::type_x) { return "foo-type-x"; }

	/// @brief 当 `T` 类型内部具备 `T::type_y` 类型时, `foo` 模板函数的特化
	///
	/// @tparam T 具备 `T::type_y` 类型定义的类型
	template <typename T>
	const char* foo(typename T::type_y) { return "foo-type-y"; }

	/// @brief 当 `foo` 函数的所有特化都不满足时, 编译器选择 `foo` 函数
	template <typename T>
	const char* foo(T) { return "foo-type-any"; }

	// --------------------------------------------------------------------------

	/// @brief 用于判断两个类型是否相同
	///
	/// 如果模板传入了两个类型, 则 `is_same_type` 类型继承自 `std::false_type`
	///
	/// @tparam T1 类型 1
	/// @tparam T2 类型 2
	template<typename T1, typename T2>
	struct is_same_type : std::false_type { };

	/// @brief 对 `is_same_type` 类型进行特化, 令两个类型一致
	///
	/// 对 `is_same_type` 类型进行特化, 当两个泛型参数类型一致时, 令 `is_same_type`
	/// 类型继承自 `std::true_type`
	///
	/// @tparam T1 类型
	template<typename T1>
	struct is_same_type<T1, T1> : std::true_type { };

	/// @brief 检测指定类型是否包含默认构造器
	///
	/// @tparam T 带检测类型
	template<typename T>
	class is_default_constructible {
	private:
		/// @brief 定义模板方法, 具备两个模板参数
		///
		/// - 第一个模板参数 (`U`) 为要检测的目标类型
		///
		/// - 第二个模板参数 (匿名) 为通过 `decltype` 运算符推断的 `U` 类型默认构造器类型
		///
		/// 当 `U()` 存在 (即 `U` 类型具备默认构造器) 时, 当前模板方法推断成功, 返回 `std::true_type` 结果;
		/// 当 `U()` 不存在 (即 `U` 类型没有默认构造器) 时, 当前模板方法推断错误, 同时, 后面的 `test`
		/// 模板方法推断成功
		///
		/// @tparam U 要检测的目标类型
		/// @param 该参数仅用于占位, 并无实际意义, 任何类型均可, 其目的是: 令两个 `test` 方法既可以形成重载, 又可以传递同样的参数,
		///       可以为一个 `test` 方法定义任意类型参数, 另一个 `test` 方法定义 `...` 参数 (表示任意参数)
		/// @return `std::true_type` 类型实例
		template<typename U, typename = decltype(U())>
		static auto test(void*) { return std::true_type(); }

		/// @brief 定义模板方法, 具备一个模板参数
		///
		/// 当 `U` 类型不具备默认构造器时, `decltype(U())` 推断失败, 且根据 SFINAE 特性,
		/// 编译器会尝试匹配当前模板函数 (只具备一个模板参数)
		///
		/// @tparam U 要检测的目标类型
		/// @param 该参数仅用于占位, 并无实际意义, 任何类型均可, 其目的是: 令两个 `test` 方法既可以形成重载, 又可以传递同样的参数,
		///       可以为一个 `test` 方法定义任意类型参数, 另一个 `test` 方法定义 `...` 参数 (表示任意参数)
		/// @return `std::false_type` 类型实例
		template<typename U>
		static auto test(...) { return std::false_type(); }

	public:
		/// @brief 常量值
		///
		/// 该常量值为: 调用 `test` 方法, 如果 `T` 类型有默认构造器, 则 `test` 方法返回 `std::true_type` 类型实例,
		/// 如果 `T` 类型没有默认构造器, 则 `test` 方法返回 `std::false_type` 类型实例;
		///
		/// 通过 `is_same_type` 类型比较结果后, `T` 类型具备默认构造器时值为 `true`, 否则值为 `false`
		static constexpr bool value = is_same_type<decltype(test<T>(nullptr)), std::true_type>::value;
	};

#if !__ge_cxx17
	// 当 C++ 版本低于 17, 模板类中定义的 `static` 类型变量需要在类之外进行声明
	template <typename T>
	constexpr bool is_default_constructible<T>::value;
#endif

	// --------------------------------------------------------------------------

#if __ge_cxx17
	template <typename..._Args> using __void_t = std::void_t<_Args...>;
#else
	/// @brief 定义模板类型, 无论模板参数为何, 其 `make_void<T>::type` 都为 `void` 类型
	///
	/// @tparam ...T 任意模板参数
	template<typename...T>
	struct make_void {
		using type = void;
	};

	/// @brief 定义 `void_t` 类型
	///
	/// 在 C++ 17 中, 引入了原生的 `void_t` 类型, 定义如下:
	///
	/// `template<typename...> using void_t = void;`
	///
	/// @tparam ...T 任意模板参数列表
	template<typename...T>
	using __void_t = typename make_void<T...>::type;
#endif

	/// @brief 用于检测指定类型是否包含 `-` 运算符
	///
	/// C++ 20 版本之前, 没有提供直接检测类型方法的办法, 但可以使用 C++ 的模板特性间接达成目标;
	///
	/// `has_operator_sub` 类型的基本原理是:
	///
	/// 1. `has_operator_sub` 类型具备两个模板参数, 默认继承自 `std::false_type`,
	///   其中 `T` 参数表示要检测的目标类型;
	///
	/// 2. 对 `has_operator_sub` 进行偏特化, 令其第二个模板参数为
	///   `void_t<decltype(declval<T>() - declval<const T&>())>` 类型,
	///   如果第二个模板参数偏特化成功 (即类型 `T` 具备 `-` 运算符), 则 `has_operator_sub`
	///   将继承自 `std::true_type`;
	///
	/// 整体借助了 C++ 的 SFINAE 特性, 即所给类型导致模板参数无效时, 不会立即编译失败,
	/// 而是尝试模板参数的其它展开方式
	///
	/// `std::declval` 函数用于获取所给类型的 "右值引用" 而无需对类型进行实例化, 故:
	/// `declval<T>() - declval<const T&>()` 表示 `-` 运算符方法的引用;
	///
	/// 接下来, 即通过 `decltype` 关键字对方法引用进行类型推断, 获得 `-` 方法返回值类型;
	///
	/// 也就是说, 只要 `T` 类型具备 `-` 运算符, `has_operator_sub` 类型的偏特化会成立,
	/// 从而 `has_operator_sub<T>` 继承自 `std::true_type` 类型, 否则会继承自 `std::false_type`
	/// 类型, 从而完成 `T` 类型是否包含 `-` 运算符的检测
	///
	/// @tparam T 待检测类型
	template<typename T, typename = void>
	struct has_operator_sub : std::false_type { };

	/// @brief `has_operator_sub` 类型的偏特化定义
	///
	/// @tparam T 待检测类型
	template<typename T>
	struct has_operator_sub<
		T,
		__void_t<decltype(std::declval<T>() - std::declval<const T&>())>
	> : std::true_type { };

	// --------------------------------------------------------------------------

	/// @brief 检测类型是否包含 `+` 运算符
	template<typename T, typename = void>
	struct has_operator_add : std::false_type { };

	template<typename T>
	struct has_operator_add<
		T,
		__void_t<decltype(std::declval<T>() + std::declval<const T&>())>
	> : std::true_type { };

	/// @brief 定义模板函数, 并通过 `std::enable_if` 对模板参数检测
	///
	/// 如果 `T` 类型具备 `+` 运算符, 则模板参数生效, 该模板函数可以正确编译, 否则模板参数失效, 编译失败
	///
	/// @tparam T 待检测模板参数
	/// @param x T 类型参数
	/// @param y T 类型参数
	/// @return 两个参数之和
	template<
		typename T,
		typename = typename std::enable_if<has_operator_add<T>::value, T>::type
	>
	T add(T x, T y) { return x + y; }

	/// @brief 定义模板函数, 并通过 `std::enable_if` 对函数返回值类型进行定义
	///
	/// 如果 `T` 类型具备 `-` 运算符, 则函数返回值生效, 函数编译成功, 否则函数编译失败
	///
	/// @tparam T 待检测模板参数
	/// @param x T 类型参数
	/// @param y T 类型参数
	/// @return 两个参数之和
	template<typename T>
	typename std::enable_if<has_operator_sub<T>::value, T>::type
		sub(T x, T y) { return x - y; }

	// --------------------------------------------------------------------------

	/// @brief 利用 SFINAE 对模板类的泛型参数进行约束
	///
	/// 利用模板的偏特化, 即可利用 SFINAE 特性对模板类型进行约束, 为此, C++ 提供了
	/// `std::enable_if_t` 类型, 具体方式为:
	///
	/// 1. 定义模板类, 且除了所需模板参数 `T` 外, 额外增加 `void` 类型匿名模板参数;
	///
	/// 2. 定义类型的偏特化模板, 将匿名模板参数特化为
	///   `std::enable_if_t<has_operator_sub<T>::value>` 类型;
	///
	/// `std::enable_if_t` 模板的参数为一个 `bool` 常量值, 如果该值为 `true`,
	/// 则 `std::enable_if_t` 类型生效, 否则 `std::enable_if_t` 类型无效,
	/// 导致当前模板类无效
	///
	/// 利用 SFINAE 机制配合 `std::enable_if_t` 模板, 即可对模板类的其它模板参数进行检测,
	/// 如果不符合条件, 则 `std::enable_if_t` 类型失效, 此时具备 `void`
	/// 类型匿名模板参数的模板生效;
	///
	/// C++ 20 之后, 提供了更方便的模式对模板参数, 参考 `concept.hpp` 中的介绍
	///
	/// @tparam T 要检测的模板参数
	template<typename T, typename = void>
	struct Subtract { };

	/// @brief 对模板参数进行检测
	///
	/// 当 `T` 类型具备 `-` 运算符, 则 `has_operator_sub<T>:value` 为 `true`,
	/// 从而 `std::enable_if_t<...>` 类型生效, 当前模板类型生效;
	///
	/// 反之, 当前模板类失效, 且上一个 `Subtract` 生效, 完成类型检测
	///
	/// @tparam T 要检测的模板参数
	template<typename T>
	class Subtract<T, std::enable_if_t<has_operator_sub<T>::value>> {
	private:
		T _val;
	public:
		/// @brief 参数构造器
		///
		/// @param val `T` 类型参数
		Subtract(T val) : _val(val) { }

		/// @brief 拷贝构造器
		Subtract(const Subtract&) = default;

		/// @brief 析构函数
		virtual ~Subtract() { }

		/// @brief 重载赋值运算符
		///
		/// @return 当前对象引用
		Subtract& operator=(const Subtract&) = default;

		/// @brief 执行减法操作
		///
		/// 将当前实例中存储的 `T` 类型变量和参数传入的 `T` 类型参数相减, 返回结果
		///
		/// @param val 减数
		/// @return 相减结果
		Subtract& sub(const T& val) {
			_val = _val - val;
			return *this;
		}

		/// @brief 获取当前实例中保存的 `T` 类型变量的可变引用
		///
		/// @return `T` 类型变量的可变引用
		T& value() { return _val; }

		/// @brief 获取当前实例中保存的 `T` 类型变量的只读引用
		///
		/// @return `T` 类型变量的只读引用
		const T& value() const { return _val; }
	};

} // namespace cxx::templated

#endif // __CPLUSPLUS_TEMPLATE__SFINAE_H
