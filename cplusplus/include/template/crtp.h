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

	class unsupport : public std::exception {
	public:
		const char* what() const noexcept override {
			return "unimplemented";
		}
	};

	template <typename _Child, bool _VIRTUAL = true>
	class Base {
	public:
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
	class Child3 : public Base<Child3, _VIRTUAL> {
		friend class Base<Child3, _VIRTUAL>;
	};


	template <typename _Child, bool _VIRTUAL>
	string polymorphism_foo(Base<_Child, _VIRTUAL>* base) {
		return base->foo();
	}

} // namespace cxx::templated

#endif //__CPLUSPLUS_TEMPLATE__CRTP_H
