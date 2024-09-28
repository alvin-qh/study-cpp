#include "oop/affine_ptr.hpp"

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_affine_ptr

using namespace cpp;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, affine_box_type) {
	Box<int> b1(100);
	ASSERT_EQ(*b1, 100);
}
