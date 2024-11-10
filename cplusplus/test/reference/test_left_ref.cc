#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "reference/left_ref.h"

#define TEST_SUITE_NAME test_cplusplus_reference__left_ref

using namespace std;

using testing::ElementsAre;

/// @brief 测试引用类型变量
///
/// 引用的本质是指针, 但和指针不同的是:
///
/// 1. 引用类型相当于其所引用变量的 "别名", 引用变量无需解引操作,
///   读取和为引用变量赋值操作都相当于对被引用变量的直接操作;
/// 2. 无法对 "右值" 进行引用操作 (包括常量和临时变量), 只能对
///   "左值" (即一个现有变量) 进行引用操作;
/// 3. 无法产生未初始化的引用变量, 即引用变量声明的同时必须引用到一个现有变量上;
/// 4. 无法对一个现有的引用变量赋予其它引用;
TEST(TEST_SUITE_NAME, reference_of_variable) {
    // 无法定义未初始化的引用变量
    // int& a;

    // 无法为右值定义引用变量
    // int& a = 100;

    // 定义变量 `a`
    int a = 100;

    // 为 `a` 变量定义引用
    int& ra = a;

    // 引用和原变量的值一致
    ASSERT_EQ(a, ra);

    // 引用和原变量的地址一致
    ASSERT_EQ(&a, &ra);

    // 修改引用值, 确认被引用变量的值也发生变化
    ra = 200;
    ASSERT_EQ(a, 200);

    int b = 300;

    // 无法改变一个引用变量引用的目标
    // 下述代码表示: 将 `b` 变量的值通过 `ra` 引用赋值给 `a` 变量,
    // 而不是将 `b` 变量的引用保存到 `ra` 中
    ra = b;
    ASSERT_EQ(a, 300);
}

/// @brief 测试指针类型引用
///
/// 指针类型变量的引用原则上和普通类型变量的引用一致,
/// 只是被引用变量是一个指针类型变量
TEST(TEST_SUITE_NAME, reference_of_pointer) {
    // 定义指针变量
    int* pa = nullptr;

    // 定义指针变量的引用
    int*& ra = pa;

    // 通过指针引用为指针赋值
    ra = new int(100);
    ASSERT_EQ(*pa, 100);

    // 通过引用的指针为其所指向的变量赋值
    *ra = 200;
    ASSERT_EQ(*pa, 200);

    delete pa;
}

/// @brief 测试引用类型函数参数
TEST(TEST_SUITE_NAME, function_reference_argument) {
    int a = 100, b = 200;
    cxx::reference::swap(a, b);
    ASSERT_EQ(a, 200);
    ASSERT_EQ(b, 100);

    string s1 = "Hello", s2 = "World";
    cxx::reference::swap(s1, s2);
    ASSERT_EQ(s1, "World");
    ASSERT_EQ(s2, "Hello");

    vector<int> v1 = { 1, 2, 3 }, v2 = { 4, 5, 6 };
    auto r = cxx::reference::merge(v1, v2);
    ASSERT_THAT(v1, ElementsAre(1, 2, 3, 4, 5, 6));
}
