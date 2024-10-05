#include <string>

#include "template/sfinae.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_template_sfinae

using namespace std;
using namespace cpp;

/// @brief 定义类型
///
/// `X` 类型内部包含 `type_x` 类型定义
///
/// 另外, 为了测试 `is_default_constructible` 模板类型,
/// `X` 类型具备默认构造器
struct X {
	typedef int type_x;
};

/// @brief 定义类型
///
/// `Y` 类型内部包含 `type_y` 类型定义
///
/// 另外, 为了测试 `is_default_constructible` 模板类型,
/// `Y` 类型不具备默认构造器 (通过定义参数构造器, 取消默认构造器)
struct Y {
	typedef int type_y;

	Y(int) {}
};

/// @brief 测试模板函数的 SFINAE 机制
TEST(TEST_SUITE_NAME, function_sfinae) {
	// `X::type_x` 存在, 故将匹配到 `foo(typename T::type_x)` 模板函数
	// 其它 `foo` 模板函数匹配失败
	ASSERT_EQ(foo<X>(1), "foo-type-x");

	// `X::type_y` 存在, 故将匹配到 `foo(typename T::type_y)` 模板函数
	// 其它 `foo` 模板函数匹配失败
	ASSERT_EQ(foo<Y>(1), "foo-type-y");

	// `foo(typename T::type_x)` 与 `foo(typename T::type_y)`
	// 模板均匹配失败, 故 `foo(T)` 模板函数匹配成功
	ASSERT_EQ(foo<int>(1), "foo-type-any");
}

/// @brief 测试模板类的 SFINAE 机制
TEST(TEST_SUITE_NAME, class_sfinae) {
	// 测试判断两个类型是否相同 (基本类型)
	ASSERT_TRUE((is_same_type<int, int>::value));
	ASSERT_FALSE((is_same_type<int, unsigned int>::value));

	// 为 `X` 类型定义类型别名
	typedef X XX;

	// 测试判断两个类型是否相同 (class 类型)
	ASSERT_TRUE((is_same_type<X, XX>::value));
	ASSERT_FALSE((is_same_type<X, Y>::value));

	// 测试检测类型是否包含默认构造器
	ASSERT_TRUE(cpp::is_default_constructible<X>::value);
	ASSERT_FALSE(cpp::is_default_constructible<Y>::value);
}

/// @brief 定义具备 `-` 运算符的类型
struct HasOperatorSub {
	HasOperatorSub operator-(const HasOperatorSub& t) { return t; }
};

/// @brief 定义不具备 `-` 运算符的类型
struct NoOperatorSub {};

/// @brief 测试检测类型是否包含指定方法
TEST(TEST_SUITE_NAME, detect_type_if_has_operator_sub) {
	// 检测 `int` 类型是否具备 `-` 运算符
	ASSERT_TRUE(has_operator_sub<int>::value);

	// 检测 `HasOperatorSub` 类型是否具备 `-` 运算符
	ASSERT_TRUE(has_operator_sub<HasOperatorSub>::value);

	// 检测 `NoOperatorSub` 类型是否具备 `-` 运算符
	ASSERT_FALSE(has_operator_sub<NoOperatorSub>::value);
}

/// @brief 测试通过 `enable_if` 约束模板类的泛型参数类型
TEST(TEST_SUITE_NAME, constraint_template_argument) {
	// `int` 类型具备 `-` 运算符, 故类型正常
	Subtract<int> s1(10);
	ASSERT_EQ(s1.value(), 10);

	// `string` 类型不具备 `-` 运算符, 故类型正常
	// Subtract<string> s2("Hello");
}
