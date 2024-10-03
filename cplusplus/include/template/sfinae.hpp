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
	struct X {
		typedef int type1;
	};

	struct Y {
		typedef int type2;
	};

	template <typename T> void foo(typename T::type1) {};    // Foo0
	template <typename T> void foo(typename T::type2) {};    // Foo1
	template <typename T> void foo(T) {};                    // Foo2
}

#endif // ! __CPLUSPLUS_TEMPLATE_SFINAE_H
