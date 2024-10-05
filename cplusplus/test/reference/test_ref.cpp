#include <string>

#include "reference/ref.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_reference_ref

using namespace std;
using namespace cpp;

// 测试引用类型变量
TEST(TEST_SUITE_NAME, ref_variables) {
	// 无法定义未初始化的引用变量
	// int& a;

	// 无法为右值定义引用变量
	// int& a = 100;

	// 定义变量 `a`
	int a = 100;

	// 为 `a` 变量定义引用
	int& ra = a;

	// 引用和原变量的值一致
	ASSERT_EQ(a, ra);

	// 引用和原变量的地址一致
	ASSERT_EQ(&a, &ra);

	ra = 200;
	ASSERT_EQ(a, 200);

	int b = 300;

	// 无法改变一个引用变量引用的目标
	// 下述代码表示: 将 `b` 变量的值通过 `ra` 引用赋值给 `a` 变量,
	// 而不是将 `b` 变量的引用保存到 `ra` 中
	ra = b;
	ASSERT_EQ(a, 300);
}

TEST(TEST_SUITE_NAME, pointer_ref) {
	int a = 100;

	int* pa = &a;
	int& ra = *pa;

	ASSERT_EQ(a, ra);
	ASSERT_EQ(&a, &ra);
}

TEST(TEST_SUITE_NAME, ref_const_variables) {
	const int a = 100;
	const int& ra = a;

	ASSERT_EQ(a, ra);
	ASSERT_EQ(&a, &ra);
}

/// @brief 测试引用类型函数参数
TEST(TEST_SUITE_NAME, ref_arguments) {
	int a = 100, b = 200;
	cpp::swap(a, b);
	ASSERT_EQ(a, 200);
	ASSERT_EQ(b, 100);

	string s1 = "Hello", s2 = "World";
	cpp::swap(s1, s2);
	ASSERT_EQ(s1, "World");
	ASSERT_EQ(s2, "Hello");
}
