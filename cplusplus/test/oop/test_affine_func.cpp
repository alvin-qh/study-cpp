#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "oop/affine_func.hpp"

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_affine_func

using namespace cpp;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, affine_func) {
	Addition add(100);

	ASSERT_EQ(300, add(200));
	ASSERT_EQ(600, add(200, 300));
}

#pragma clang diagnostic pop
