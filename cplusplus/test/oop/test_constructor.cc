#include <gtest/gtest.h>

#include "oop/constructor.h"

#define TEST_SUITE_NAME test_cplusplus_oop__constructor

using namespace cxx::oop;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, default_constructor) {
    Constructor c1;
    ASSERT_EQ(c1.value(), 0.0);

    Constructor c2{};
    ASSERT_EQ(c1.value(), 0.0);
}

/// @brief 测试参数构造器
///
/// 如果参数构造器仅有一个参数
TEST(TEST_SUITE_NAME, parameterized_constructor) {
    Constructor c1(1.0);
    ASSERT_EQ(c1.value(), 1.0);

    Constructor c2{ 2.0 };
    ASSERT_EQ(c2.value(), 2.0);

    Constructor c3 = 3.0;
    ASSERT_EQ(c3.value(), 3.0);
}
