#include <gtest/gtest.h>

#include "oop/class.h"

#define TEST_SUITE_NAME test_cplusplus_oop__class

using namespace cxx::oop;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, default_constructor) {
    AClass c1;
    ASSERT_EQ(0, c1.value());

    // 调用默认构造器的另一种形式
    AClass c2 = AClass();
    ASSERT_EQ(0, c2.value());

    // 在"堆"上调用默认构造器
    AClass* pc = new AClass();
    ASSERT_EQ(0, pc->value());

    delete pc;
}

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, arguments_constructor) {
    AClass c1(100);
    ASSERT_EQ(100, c1.value());

    AClass c2 = AClass(100);
    ASSERT_EQ(100, c2.value());

    // 在"堆"上调用参数构造器
    AClass* p3 = new AClass(100);
    ASSERT_EQ(100, p3->value());

    delete p3;
}

/// @brief 测试拷贝构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
    AClass c1(100);

    // 调用拷贝构造器的语法格式 1
    AClass c2 = c1;
    ASSERT_EQ(100, c1.value());

    // 调用拷贝构造器的语法格式 2
    AClass c3(c1);
    ASSERT_EQ(100, c3.value());

    // 调用拷贝构造器的语法格式 3
    AClass p4 = AClass(c1);
    ASSERT_EQ(100, p4.value());

    // 调用拷贝构造器的语法格式 3
    AClass* pc = new AClass(c1);
    ASSERT_EQ(100, pc->value());

    delete pc;
}

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
    AClass c1(100), c2;

    // 调用重载赋值运算符
    c2 = c1;
    ASSERT_EQ(100, c2.value());
}

/// @brief 测试比较运算符的重载
TEST(TEST_SUITE_NAME, equal_operator_override) {
    AClass c1(100), c2;
    ASSERT_FALSE(c1 == c2);
    ASSERT_TRUE(c1 != c2);

    c2 = c1;
    ASSERT_FALSE(c1 != c2);
    ASSERT_TRUE(c1 == c2);
}
