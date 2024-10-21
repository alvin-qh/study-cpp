#include <gtest/gtest.h>

#include "template/concept.hpp"
#include "../test.h"

#include <string>

#define TEST_SUITE_NAME test_cplusplus_template_concept

using namespace std;
using namespace cpp::temp;

/// @brief 测试通过 `concept` 方式对泛型类型的约束
TEST(TEST_SUITE_NAME, concept_definition) {
	ASSERT_EQ(add(1, 2), 3);
	ASSERT_EQ(cpp::number_to_fixed(add(1.1, 2.2), 2), 3.3);

	// `add` 函数不支持非数值类型参数
	// ASSERT_EQ("Hello World", add(string("Hello "), string("World")));
}

/// @brief 测试通过 `requires` 方式对泛型类型的约束
TEST(TEST_SUITE_NAME, requires_definition) {
	ASSERT_EQ(Subtract<int>::sub(2, 1), 1);

	// 由于 `std::string` 类型不包括 `-` 运算符, 故 `Subtract<string>` 模板编译失败
	// ASSERT_EQ(Subtract<string>::sub("Hello World", "Hello "), "World");
}

TEST(TEST_SUITE_NAME, concept_combine) {
	ASSERT_EQ(multiply(10, 20), 200);

	// multiply("hello", "word");
}

TEST(TEST_SUITE_NAME, concept_rule) {
	int n = 1;
	ASSERT_EQ(increment(n), 2);

	double f = 1.1;
	ASSERT_EQ(increment(f), 2.1);
}
