#include <gtest/gtest.h>

#include "template/crtp.h"

#define TEST_SUITE_NAME test_cplusplus_template__CRTP

using namespace cxx::templated;

/// @brief 测试 C++ 的 CRTP 特性
/// 
/// 通过
TEST(TEST_SUITE_NAME, crtp) {
    Child1 c1;
    ASSERT_EQ(c1.foo(), "Child1");

    Child2 c2;
    ASSERT_EQ(c2.foo(), "Child2");

    Base<Child1>* base = &c1;
    ASSERT_EQ(base->foo(), "Child1");

    // b1 = &c2;

    ASSERT_EQ(polymorphism_foo(&c1), "Child1");
    ASSERT_EQ(polymorphism_foo(&c2), "Child2");

#ifndef _SANITIZE_LEAK
    Child3<false> c3_1;
    ASSERT_EQ(c3_1.foo(), "Base");

    Child3<true> c3_2;
    ASSERT_THROW(polymorphism_foo(&c3_2), unsupport);
#endif
}
