#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__CRTP_H
#define __CPLUSPLUS_TEMPLATE__CRTP_H

#include <string>

/// CRTP 是 C++ 模板的一种使用范式, 称为 "奇异递归模板模式 (Curiously Recurring Template Pattern)"
///
/// 在一些情况下, CRTP 可以替代 C++ OOP 中的基础和多态 (虚函数), 并且不会引入虚表 (VTable)
/// 从而导致性能下降和内存使用升高
///
/// https://zhuanlan.zhihu.com/p/142407249

namespace cxx::templated {
	using namespace std;

	/// @brief 定义异常类型, 表示一个 "虚拟" 方法未被子类实现
	class unsupport : public std::exception {
	public:
		/// @brief 返回异常描述信息
		///
		/// @return 异常描述信息字符串
		const char* what() const noexcept override {
			return "unimplemented";
		}
	};

	/// @brief 定义父类类型, 该父类类型方法内部通过 "奇异递归模板" 模式调用继承其子类的对应方法
	///
	/// @tparam _Child 表示子类类型的模板参数
	/// @tparam _VIRTUAL `bool` 类型模板参数, 表示父类方法是否为 "虚函数". "奇异递归模板"
	///                         模式表示的虚函数并不是真的虚函数 (没有 `VTable‵ 表), 而是当函数无法通过子类型指针调用时,
	///                         抛出异常
	template <typename _Child, bool _VIRTUAL = true>
	class Base {
	public:
		/// @brief 定义函数, 通过将当前 `this‵ 指针强制转为 `_Child` 子类型指针, 在函数内部调用子类型的 `_foo_impl` 函数来模拟子类重写
		///        (`Override`) 父类同名函数的目的
		///
		/// @return 返回字符串用于标示具体执行的是父类或子类函数
		string foo() {
			return static_cast<_Child*>(this)->_foo_impl();
		}
	private:
		/// @brief 定义兜底方法实现
		///
		/// 一旦子类没有重写该方法, 则通过子类对象将调用到父类该方法, 导致抛出异常,
		/// 故该方法的主要作用是防止子类未重写父类方法
		///
		/// 当然, 该方法也可以具备默认实现, 无需子类一定覆盖
		///
		/// @return 类名称字符串
		string _foo_impl() {
			if constexpr (_VIRTUAL) {
				throw unsupport();
			}
			return "Base";
		}
	};

	class Child1 : public Base<Child1> {
	public:
		string _foo_impl() { return "Child1"; }
	};

	class Child2 : public Base<Child2> {
		/// @brief 必须将父类 `Base<Child1>` 声明为当前子类的友元类
		/// 否则 `Base<Child1>` 类内部无法访问到当前友元类的私有成员
		friend class Base<Child2>;
	private:
		string _foo_impl() { return "Child2"; }
	};

	template <bool _VIRTUAL>
	class Child3 : public Base<Child3<_VIRTUAL>, _VIRTUAL> {
		friend class Base<Child3>;
	};

	template <typename _Child, bool _VIRTUAL>
	string polymorphism_foo(Base<_Child, _VIRTUAL>* base) {
		return base->foo();
	}

} // namespace cxx::templated

#endif //__CPLUSPLUS_TEMPLATE__CRTP_H
