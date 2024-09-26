#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "template/func.hpp"

#include <gtest/gtest.h>
#include "../test.h"

/**
 * 测试泛型函数
 *
 * `template/func.hpp` 中的 `add` 函数的泛型参数 `T` 可为任意类型,
 * 该函数返回两个 `T` 类型参数的和
 */
TEST(test_cplusplus_template_func, add) {
	// int 类型
	EXPECT_EQ(3, cpp::add(1, 2));

	// double 类型
	EXPECT_EQ(3.3, cpp::number_to_fixed(cpp::add(1.1, 2.2), 2));

	// std::string 类型
	EXPECT_EQ("Hello World", cpp::add(std::string("Hello "), std::string("World")));
}

#pragma clang diagnostic pop
