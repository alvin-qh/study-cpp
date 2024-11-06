#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop__const_1

#include <string>

#include "oop/const.h"

using namespace std;
using namespace cxx::oop;

TEST(TEST_SUITE_NAME, const_class_field) {
    // 1. 测试 `constexpr` 修饰的变量
    static_assert(CE_MAX_N == 50);
    static_assert(CE_MAX_M == 150);
    static_assert(CE_STR_1 == "Alvin");

    // 2. 测试 `const` 修饰的变量

    // static_assert(NAME_2 == "Emma");
    ASSERT_EQ(CE_STR_2, "Emma");

    // 将只读变量的引用转为可读写变量引用, 并修改变量的值
    const_cast<string&>(CE_STR_2) = "Lucy";
    ASSERT_EQ(CE_STR_2, "Lucy");

    ConstField cf;
    ASSERT_EQ(cf.c_str, "AA");

    // 一般情况下, 无法修改只读字段的值
    // cf.c_str = "AAA";

    const_cast<string&>(cf.c_str) = "AAA";
    ASSERT_EQ(cf.c_str, "AAA");
}
