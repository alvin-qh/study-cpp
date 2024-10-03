#include <gtest/gtest.h>

#include "../test.h"
#include "template/sfinae.hpp"

#define TEST_SUITE_NAME test_cplusplus_template_sfinae

using namespace cpp;

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
