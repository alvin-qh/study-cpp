#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "template/concept.hpp"

#include <gtest/gtest.h>
#include "../test.h"

/**
 * 测试泛型函数对泛型类型的约束
 *
 * `template/concept.hpp` 中的 `add` 函数的泛型参数 `T` 只接收数值类型参数,
 * 非数值类型参数将会导致编译错误
 */
TEST(test_cplusplus_template_func, add) {
	EXPECT_EQ(3, cpp::add(1, 2));
	EXPECT_EQ(3.3, cpp::number_to_fixed(cpp::add(1.1, 2.2), 2));

	// `add` 函数不支持非数值类型参数
	// EXPECT_EQ("Hello World", cpp::add(std::string("Hello "), std::string("World")));
}

#pragma clang diagnostic pop
