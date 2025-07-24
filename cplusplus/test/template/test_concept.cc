#if __ge_cxx20

#include <gtest/gtest.h>

#include "template/concept.h"
#include "../test.h"

#include <string>

#define TEST_SUITE_NAME test_cplusplus_template__concept

using namespace std;
using namespace cxx::templated;

/// @brief 测试通过 `concept` 方式对泛型类型的约束
TEST(TEST_SUITE_NAME, concept) {
    ASSERT_EQ(add1(1, 2), 3);
    ASSERT_EQ(cxx::number_to_fixed(add2(1.1, 2.2), 2), 3.3);

    // 函数不支持非数值类型参数
    // add1(string("A"), string("B"));

    // 函数不支持非数值类型
    // add2(string("A"), string("B"));
}

/// @brief 测试 `concept` 与 `bool` 常量表达式的组合
TEST(TEST_SUITE_NAME, concept_with_boolean_expression) {
    ASSERT_EQ(add3(2, 1), 3);

    // 函数不支持非数值类型
    // add3(string("A"), string("B"));

    // 函数不支持没有加号运算的类型
    // add3("A", "B");
}

/// @brief 测试通过 `requires` 关键字约束模板参数
TEST(TEST_SUITE_NAME, requires) {
    ASSERT_EQ(add4(2, 1), 3);

    // 函数不支持非数值类型
    // add4(string("A"), string("B"));

    // 函数不支持没有加号运算的类型
    // add4("A", "B");
}

/// @brief 测试通过 `requires` 关键字约束 `concept` 的定义
TEST(TEST_SUITE_NAME, concept_with_requires_specified_operate) {
    ASSERT_EQ(add5(10, 20), 30);

    // 函数不支持非数值类型
    // add5(string("A"), string("B"));

    // 函数不支持没有加号运算的类型
    // add5("A", "B");
}

/// @brief 测试通过 `requires` 关键字约束 `concept` 的定义
TEST(TEST_SUITE_NAME, concept_with_requires_specified_return) {
    ASSERT_EQ(add6(10, 20), 30);

    // 函数不支持非数值类型
    // add6(string("A"), string("B"));

    // 函数不支持没有加号运算的类型
    // add6("A", "B");
}

#endif // __ge_cxx20
