#include <gtest/gtest.h>

#include "template/crtp.h"

#define TEST_SUITE_NAME test_cplusplus_template__CRTP

using namespace cxx::templated;

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

    Child3<false> c3;
    ASSERT_THROW(c3.foo(), "Base");

    ASSERT_THROW(polymorphism_foo(&c3), unsupport);
}
