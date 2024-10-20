#include <gtest/gtest.h>

#include "template/affine_func.hpp"

#define TEST_SUITE_NAME test_cplusplus_affine_func

using namespace cpp::temp;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, affine_func) {
	// 实例化仿函数对象
	AffineFunc func(100);
	ASSERT_EQ(100, func.value());

	// 测试 `()` 运算符重载, 即调用仿函数
	ASSERT_EQ(300, func(200));
	ASSERT_EQ(600, func(200, 300));
}
