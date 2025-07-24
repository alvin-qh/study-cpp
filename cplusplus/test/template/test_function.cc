#include <gtest/gtest.h>

#include "template/function.h"
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_template__function

using namespace std;
using namespace cxx::templated;

/// @brief 测试泛型函数
TEST(TEST_SUITE_NAME, templated_function) {
    // int 类型, 调用 `template<typename T> T add(const T&, const T&)`
    ASSERT_EQ(3, add(1, 2));

    // double 类型, 调用 `template<typename T> T add(const T&, const T&)`
    ASSERT_EQ(3.3, cxx::number_to_fixed(add(1.1, 2.2), 2));

    // string 类型, 调用 `template<> string add(const string&, const string&)`
    ASSERT_EQ("Hello World", add(string("Hello"), string("World")));
}

/// @brief 测试仿函数类型
TEST(TEST_SUITE_NAME, affine_func) {
    // 实例化仿函数对象
    AffineFunc<int> func(100);
    ASSERT_EQ(100, func.value());

    // 测试 `()` 运算符重载, 即调用仿函数
    ASSERT_EQ(300, func(200));
    ASSERT_EQ(600, func(200, 300));
}