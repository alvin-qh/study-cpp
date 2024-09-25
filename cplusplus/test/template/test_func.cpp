#include "template/func.hpp"

#include <gtest/gtest.h>
#include "../test.h"

/**
 * 测试泛型函数
 */
TEST(test_template_func, add) {
	EXPECT_EQ(3, add(1, 2));
	EXPECT_EQ(3.3, number_to_fixed(add(1.1, 2.2), 2));
}
