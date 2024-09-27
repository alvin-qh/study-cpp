#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "template/func.hpp"

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_template_func

using namespace std;
using namespace cpp;

/// @brief 测试泛型函数
TEST(TEST_SUITE_NAME, add) {
	// int 类型
	EXPECT_EQ(3, add(1, 2));

	// double 类型
	EXPECT_EQ(3.3, number_to_fixed(add(1.1, 2.2), 2));

	// string 类型
	EXPECT_EQ("Hello World", add(string("Hello "), string("World")));
}

#pragma clang diagnostic pop
