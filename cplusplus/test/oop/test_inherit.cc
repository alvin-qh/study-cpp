#include <gtest/gtest.h>

#include "oop/inherit.h"

#define TEST_SUITE_NAME test_cplusplus_oop__inherit

using namespace cxx::oop;

/// @brief 测试类型继承
TEST(TEST_SUITE_NAME, inherit) {
    // 测试参数构造器
    ChildClass c1(1, 1.1);
    ASSERT_EQ(1, c1.a());
    ASSERT_EQ(1.1, c1.b());

    // 测试拷贝构造器
    ChildClass c2 = c1;
    ASSERT_EQ(1, c2.a());
    ASSERT_EQ(1.1, c2.b());
}

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
    ChildClass c1(1, 1.1), c2;

    // 调用重载赋值运算符
    c2 = c1;
    ASSERT_EQ(1, c2.a());
    ASSERT_EQ(1.1, c2.b());
}

/// @brief 测试比较运算符的重载
TEST(TEST_SUITE_NAME, equal_operator_override) {
    ChildClass c1(1, 1.1), c2;
    ASSERT_FALSE(c1 == c2);
    ASSERT_TRUE(c1 != c2);

    c2 = c1;
    ASSERT_TRUE(c1 == c2);
    ASSERT_FALSE(c2 != c2);

    ChildClass c3(2, 2.2);
    ASSERT_TRUE(c1 != c3);
    ASSERT_FALSE(c1 == c3);
}

/// @brief 测试多态特性
TEST(TEST_SUITE_NAME, virtual_method) {
    // 当指针指向 `BaseClass` 实例时, 调用 `BaseClass::to_string` 方法
    const BaseClass* pb = new BaseClass(1);
    ASSERT_EQ("BaseClass(1)", pb->to_string());

    delete pb;

    // 当指针指向 `ChildClass` 实例时, 调用 `ChildClass::to_string` 方法
    pb = new ChildClass(1, 1.1);
    ASSERT_EQ("ChildClass(1, 1.1)", pb->to_string());

    delete pb;
}

/// @brief 测试析构函数
TEST(TEST_SUITE_NAME, destructor) {
    uint32_t destroy_count = 0;

    // 当 `ChildClass` 实例被销毁后, `destroy_count` 值加 2, 表示 `ChildClass`
    // 的析构函数 以及 `BaseClass` 的析构函数各执行了一次
    {
        ChildClass p;
        p.__set_destroy_count_ptr(&destroy_count);
    }
    ASSERT_EQ(2, destroy_count);
}
