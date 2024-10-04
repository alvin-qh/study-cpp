#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "../test.h"
#include "template/sfinae.hpp"

#define TEST_SUITE_NAME test_cplusplus_template_sfinae

using namespace cpp;

/// @brief 定义类型, 内部包含 `type_x` 类型定义
///
/// `type_x` 类型为 `int` 类型的别名
struct X {
	typedef int type_x;

	X() {}
};

/// @brief 定义类型, 内部包含 `type_y` 类型定义
///
/// `type_y` 类型为 `int` 类型的别名
struct Y {
	typedef int type_y;

	Y(int) {}
};

/// @brief 测试模板函数的 SFINAE
TEST(TEST_SUITE_NAME, function_sfinae) {
	const char* r = nullptr;

	// `X::type_x` 存在, 故将匹配到 `foo(typename T::type_x)` 模板函数
	// 其它 `foo` 模板函数匹配失败
	r = foo<X>(1);
	ASSERT_EQ(r, "foo-type-x");

	// `X::type_y` 存在, 故将匹配到 `foo(typename T::type_y)` 模板函数
	// 其它 `foo` 模板函数匹配失败
	r = foo<Y>(1);
	ASSERT_EQ(r, "foo-type-y");

	// `foo(typename T::type_x)` 与 `foo(typename T::type_y)`
	// 模板均匹配失败, 故 `foo(T)` 模板函数匹配成功
	r = foo<int>(1);
	ASSERT_EQ(r, "foo-type-any");
}

TEST(TEST_SUITE_NAME, class_sfinae) {
	bool same = is_same_type<int, int>::value;
	ASSERT_TRUE(same);

	same = is_same_type<int, unsigned int>::value;
	ASSERT_FALSE(same);

	typedef X XX;

	same = is_same_type<X, XX>::value;
	ASSERT_TRUE(same);

	same = is_same_type<X, Y>::value;
	ASSERT_FALSE(same);

	bool has = is_default_constructible<X>::value;
	ASSERT_TRUE(has);

	has = is_default_constructible<Y>::value;
	ASSERT_FALSE(has);
}

/// @brief 定义具备 `-` 运算符的类型
struct HasOperatorSub {
	HasOperatorSub operator-(const HasOperatorSub& t) { return t; }
};

/// @brief 定义不具备 `-` 运算符的类型
struct NoOperatorSub { };

/// @brief 测试检测类型是否包含指定方法
TEST(TEST_SUITE_NAME, detect_type_if_has_operator_sub) {
	// 检测类型是否具备 `-` 运算符
	ASSERT_TRUE(has_operator_sub<HasOperatorSub>::value);

	// 检测类型是否具备 `-` 运算符
	ASSERT_FALSE(has_operator_sub<NoOperatorSub>::value);
}

