#include <string>

#include "reference/right_ref.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_reference_right_ref

using namespace std;
using namespace cpp;


/// @brief 测试右值引用
///
/// 所谓右值, 即只能出现在赋值运算符 "右边" 的值, 这类值均为 "临时" 值, 包括:
///
/// - 值类型函数返回值;
/// - 临时对象;
/// - 值传递的函数参数;
///
/// 这些 "临时值" 在通过赋值传递时, 会通过 C++ 的拷贝构造器或赋值操作,
/// 往往会导致源对象的销毁和新对象的产生, 带来性能损耗
///
/// 通过 `&&` 运算符, C++ 允许为右值建立引用, 称为 "右值引用",
/// 右值引用可以临时获取到右值的所有权, 通过这种方式, 即可避免额外的构造和析构动作
TEST(TEST_SUITE_NAME, make_right_reference) {
	// 常量 `100` 为右值, 为其建立引用
	int&& n1 = 100;
	ASSERT_EQ(n1, 100);

	// 可修改右值引用
	n1 = 200;
	ASSERT_EQ(n1, 200);

	// 在函数内部创建的值为临时变量, 可通过右值引用对其进行引用
	int&& n2 = []() { return 200; }();
	ASSERT_EQ(n2, 200);
}

/// @brief 判断一个值是否为右值引用
TEST(TEST_SUITE_NAME, check_if_right_reference) {
	// 临时变量/对象为右值引用
	ASSERT_TRUE(is_right_reference<int>::test(int(0)));
	ASSERT_TRUE(is_right_reference<int>::test(100));
	ASSERT_TRUE(is_right_reference<string>::test("Hello"));
	ASSERT_TRUE(is_right_reference<string>::test(string("Hello")));

	// 变量引用为左值引用, 不是右值引用
	int n = 100;
	ASSERT_FALSE(is_right_reference<int>::test(n));

	// 变量引用为左值引用, 不是右值引用
	string s = "Hello";
	ASSERT_FALSE(is_right_reference<string>::test(s));
}

/// @brief 获取左值临时的右值引用
///
/// 一些时候, 需要获取一个左值的临时 "右值引用";
/// 获取右值引用的目的是得到一个区别于 “左值引用” 的引用类型,
/// 在为发生 “移动语义” 的情况下提供类型支持
TEST(TEST_SUITE_NAME, left_to_right_reference) {
	int n1 = 100;

	ASSERT_FALSE(is_right_reference<int>::test(n1));

	// 通过 `static_cast` 操作符即可将左值引用转为右值引用
	ASSERT_TRUE(is_right_reference<int>::test(static_cast<int&&>(n1)));
}
