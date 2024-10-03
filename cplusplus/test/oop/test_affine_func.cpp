#include <gtest/gtest.h>
#include <type_traits>

#include "../test.h"
#include "oop/affine_func.hpp"

#define TEST_SUITE_NAME test_cplusplus_affine_func

using namespace cpp;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, affine_func) {
	Addition add(100);

	ASSERT_EQ(100, add.value());

	// 测试 `()` 运算符重载, 即调用仿函数
	ASSERT_EQ(300, add(200));
	ASSERT_EQ(600, add(200, 300));
}
