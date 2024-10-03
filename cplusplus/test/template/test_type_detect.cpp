#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "../test.h"
#include "template/type_detect.hpp"

#define TEST_SUITE_NAME test_cplusplus_template_type_detect

using namespace cpp;

/// @brief 定义具备 `-` 运算符的类型
struct HasOperatorSub {
	HasOperatorSub& operator-(HasOperatorSub& t) { return t; }
};

/// @brief 定义不具备 `-` 运算符的类型
struct NoOperatorSub {
};

/// @brief 测试检测类型是否包含指定方法
TEST(TEST_SUITE_NAME, detect_type_if_has_operator_sub) {
	// 检测类型是否具备 `-` 运算符
	ASSERT_TRUE(has_operator_sub<HasOperatorSub>::value);

	// 检测类型是否具备 `-` 运算符
	ASSERT_FALSE(has_operator_sub<NoOperatorSub>::value);
}
