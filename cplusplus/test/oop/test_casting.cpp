#include "oop/casting.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_casting

using namespace cpp;

class A {
protected:
	int _id;

	A(int id) :
		_id(id) {
	}
public:
	A() :
		A(100) {
	}

	virtual const char* who_am_i() const noexcept { return "class A"; }

	virtual int id() const { return _id; }
};

class B :public A {
private:
	int _tag;
public:
	B() :
		A(200),
		_tag(10) {
	}

	virtual const char* who_am_i() const noexcept override { return "class B"; }

	virtual int tag() const { return _tag; }
};

/// @brief 测试静态类型转换
///
/// `static_cast` 操作符的作用包括:
///
/// 1. 基本类型之间进行转换
/// 2. `void*` 指针到任意基本类型指针的转换;
/// 3. 具备继承关系的子类与父类指针 (或引用) 的转换
///
/// `static_cast` 在进行父类和子类指针转换时, 并不会检查指针指向的实际类型, 故可能会导致转换错误
TEST(TEST_SUITE_NAME, static_casting) {
	// `int` => `double`
	int n = 100;
	double f = static_cast<double>(n);

	int* pn = &n;
	double* pf = static_cast<double*>(static_cast<void*>(pn));
	ASSERT_NE(*pf, n);

	B b;
	A* pa = static_cast<A*>(&b);
	ASSERT_EQ(pa->who_am_i(), "class B");
	ASSERT_EQ(pa->id(), 200);

	A a;
	B* pb = static_cast<B*>(&a);
	ASSERT_EQ(pb->who_am_i(), "class A");
	ASSERT_EQ(pb->id(), 100);
	// ASSERT_EQ(pb->tag(), 10);
}
