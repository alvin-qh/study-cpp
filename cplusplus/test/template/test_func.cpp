#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "template/func.hpp"

#include <gtest/gtest.h>
#include "../test.h"

/**
 * 测试泛型函数
 */
TEST(test_cplusplus_template_func, add) {
	EXPECT_EQ(3, cpp::add(1, 2));
	EXPECT_EQ(3.3, cpp::number_to_fixed(cpp::add(1.1, 2.2), 2));
}

#pragma clang diagnostic pop
