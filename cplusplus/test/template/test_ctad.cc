#if __ge_cxx17

#include <gtest/gtest.h>

#include "template/ctad.h"

#define TEST_SUITE_NAME test_cplusplus_template__CTAD

using namespace std;
using namespace cxx::templated;

/// @brief 测试模板类型推断指导
TEST(TEST_SUITE_NAME, type_deduction) {
    // 实例化对象, 并指定构造器参数为 `const char*` 类型,
    // 按照推断指引, 模板参数将被推断为 `std::string` 类型
    CTAD c1("hello", "world");
    ASSERT_TRUE((c1.is_same_type<string, string>()));
    ASSERT_EQ(c1.v1().size(), 5);
    ASSERT_EQ(c1.v2().size(), 5);

    // 实例化对象, 并指定构造器参数为 `int` 类型,
    // 按照推断指引, 模板参数将被推断为 `double` 类型
    CTAD c2(1, 2);
    ASSERT_TRUE((c2.is_same_type<double, double>()));
    ASSERT_EQ(c2.v1(), 1.0);
    ASSERT_EQ(c2.v2(), 2.0);

    // 实例化对象, 并指定构造器参数为 `bool` 类型,
    // 实力推断指引中未定义 `bool` 参数类型的推断规则, 模板参数仍为 `bool` 类型
    CTAD c3(true, false);
    ASSERT_TRUE((c3.is_same_type<bool, bool>()));
    ASSERT_TRUE(c3.v1());
    ASSERT_FALSE(c3.v2());
}

#endif // __ge_cxx17