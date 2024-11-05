#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop__const_1

#include <string>

#include "oop/const.h"

using namespace std;
using namespace cxx::oop;

TEST(TEST_SUITE_NAME, const_class_field) {
    // 实例后常量类对象, 该对象为一个常量值
    // 常量类对象的实例化在编译期进行
    constexpr ConstClass c = ConstClass("TEST", 100, "");

    // 调用常量类对象的方法, 这些方法均为常量方法, 可以在编译期调用执行
    static_assert(static_str_cmp(c.name(), "TEST") == 0);
    static_assert(c.value() == 100);

    // 在运行期也可以调用常量类型对象的方法, 这些方法将被编译为常量值
    ASSERT_STREQ(c.name(), "TEST");
    ASSERT_EQ(c.value(), 100);
}
