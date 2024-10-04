#include "template/concept.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_template_concept

using namespace cpp;

/// @brief 测试泛型函数对泛型类型的约束
TEST(TEST_SUITE_NAME, add) {
	EXPECT_EQ(3, add(1, 2));
	EXPECT_EQ(3.3, number_to_fixed(add(1.1, 2.2), 2));

	// `add` 函数不支持非数值类型参数
	// EXPECT_EQ("Hello World", add(string("Hello "), string("World")));
}
