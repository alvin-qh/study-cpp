#include <gtest/gtest.h>

#include <tuple>

#include "oop/operator.h"

#define TEST_SUITE_NAME test_cplusplus_oop__operator

using namespace std;
using namespace cxx::oop;

/// @brief 测试拷贝赋值运算符重载
TEST(TEST_SUITE_NAME, operator_assign) {
    Operator o1(1, 2, 3), o2;

    // 调用拷贝赋值运算符
    o2 = o1;
    ASSERT_EQ(o2.x(), 1);
    ASSERT_EQ(o2.y(), 2);
    ASSERT_EQ(o2.z(), 3);
}

/// @brief 测试移动赋值运算符
TEST(TEST_SUITE_NAME, operator_move_assign) {
    Operator o1(1, 2, 3), o2;

    // 调用移动赋值运算符
    o2 = std::move(o1);
    ASSERT_EQ(o2.x(), 1);
    ASSERT_EQ(o2.y(), 2);
    ASSERT_EQ(o2.z(), 3);

    // `o1` 对象的内容已被移动
    ASSERT_EQ(o1.x(), 0);
    ASSERT_EQ(o1.y(), 0);
    ASSERT_EQ(o1.z(), 0);
}

/// @brief 测试加法运算符重载, 将两个对象相加
TEST(TEST_SUITE_NAME, operator_addition) {
    Operator o1(1, 2, 3), o2(10, 20, 30);

    Operator r = o1 + o2;
    ASSERT_EQ(r.x(), 11);
    ASSERT_EQ(r.y(), 22);
    ASSERT_EQ(r.z(), 33);

    r = o2 + o1;
    ASSERT_EQ(r.x(), 11);
    ASSERT_EQ(r.y(), 22);
    ASSERT_EQ(r.z(), 33);

    tuple<double, double, double> tup = make_tuple(10.0, 20.0, 30.0);
    r = o1 + tup;
    ASSERT_EQ(r.x(), 11);
    ASSERT_EQ(r.y(), 22);
    ASSERT_EQ(r.z(), 33);

    r = tup + o1;
    ASSERT_EQ(r.x(), 11);
    ASSERT_EQ(r.y(), 22);
    ASSERT_EQ(r.z(), 33);
}

/// @brief 测试减法运算符重载, 将两个对象相减
///
/// 该减法运算符重载是通过 `Operator` 类型的友元函数完成
TEST(TEST_SUITE_NAME, operator_subtraction) {
    Operator o1(1, 2, 3), o2(10, 20, 30);

    Operator r = o1 - o2;
    ASSERT_EQ(r.x(), -9);
    ASSERT_EQ(r.y(), -18);
    ASSERT_EQ(r.z(), -27);

    r = o2 - o1;
    ASSERT_EQ(r.x(), 9);
    ASSERT_EQ(r.y(), 18);
    ASSERT_EQ(r.z(), 27);

    tuple<double, double, double> tup = make_tuple(10.0, 20.0, 30.0);
    r = o1 - tup;
    ASSERT_EQ(r.x(), -9);
    ASSERT_EQ(r.y(), -18);
    ASSERT_EQ(r.z(), -27);

    r = tup - o1;
    ASSERT_EQ(r.x(), 9);
    ASSERT_EQ(r.y(), 18);
    ASSERT_EQ(r.z(), 27);
}

/// @brief 测试下标操作符重载, 获取指定变量值
TEST(TEST_SUITE_NAME, operator_index) {
    Operator o(1, 2, 3);

    ASSERT_EQ(o[0], 1);
    ASSERT_EQ(o[1], 2);
    ASSERT_EQ(o[2], 3);
}

/// @brief 测试乘法运算符重载, 将当前对象和一个浮点数相乘
TEST(TEST_SUITE_NAME, operator_times_with_double) {
    Operator o1(1, 2, 3);

    Operator res1 = o1 * 2.0;
    ASSERT_EQ(res1.x(), 2);
    ASSERT_EQ(res1.y(), 4);
    ASSERT_EQ(res1.z(), 6);

    Operator o2(10, 20, 30);

    double res2 = o1 * o2;
    ASSERT_EQ(res2, 140);
}

/// @brief 测试乘法运算符重载, 将当前对象和另一个对象相乘
///
/// 该运算符重载返回一个浮点数
TEST(TEST_SUITE_NAME, operator_times_with_object) {
    Operator o1(1, 2, 3), o2(10, 20, 30);

    double r = o1 * o2;
    ASSERT_EQ(r, 140);
}

/// @brief 测试 `++` 运算符重载
///
/// 测试前置 `++` 以及后置 `++` 运算符重载
TEST(TEST_SUITE_NAME, operator_plus) {
    Operator o1(1, 2, 3);

    Operator o2 = ++o1;
    ASSERT_EQ(o1.x(), 2);
    ASSERT_EQ(o1.y(), 3);
    ASSERT_EQ(o1.z(), 4);

    ASSERT_EQ(o2.x(), 2);
    ASSERT_EQ(o2.y(), 3);
    ASSERT_EQ(o2.z(), 4);

    o2 = o1++;
    ASSERT_EQ(o1.x(), 3);
    ASSERT_EQ(o1.y(), 4);
    ASSERT_EQ(o1.z(), 5);

    ASSERT_EQ(o2.x(), 2);
    ASSERT_EQ(o2.y(), 3);
    ASSERT_EQ(o2.z(), 4);
}

/// @brief 测试 `--` 运算符重载
///
/// 测试前置 `--` 以及后置 `--` 运算符重载
TEST(TEST_SUITE_NAME, operator_minus) {
    Operator o1(1, 2, 3);

    Operator o2 = --o1;
    ASSERT_EQ(o1.x(), 0);
    ASSERT_EQ(o1.y(), 1);
    ASSERT_EQ(o1.z(), 2);

    ASSERT_EQ(o2.x(), 0);
    ASSERT_EQ(o2.y(), 1);
    ASSERT_EQ(o2.z(), 2);

    o2 = o1--;
    ASSERT_EQ(o1.x(), -1);
    ASSERT_EQ(o1.y(), 0);
    ASSERT_EQ(o1.z(), 1);

    ASSERT_EQ(o2.x(), 0);
    ASSERT_EQ(o2.y(), 1);
    ASSERT_EQ(o2.z(), 2);
}

/// @brief 测试三路运算符重载
TEST(TEST_SUITE_NAME, operator_three_way_compare) {
    Operator o1(1, 2, 3), o2(10, 20, 30);

    ASSERT_FALSE(o1 == o2);
    ASSERT_TRUE(o1 != o2);
    ASSERT_FALSE(o1 > o2);
    ASSERT_FALSE(o1 >= o2);
    ASSERT_TRUE(o1 < o2);
    ASSERT_TRUE(o1 <= o2);
}

/// @brief 测试运算符在子类中的继承情况
TEST(TEST_SUITE_NAME, operator_inherit) {
    OperatorChild oc1(1, 2, 3), oc2;

    oc2 = oc1;
    ASSERT_EQ(oc2.x(), 1);
    ASSERT_EQ(oc2.y(), 2);
    ASSERT_EQ(oc2.z(), 3);

    oc2 = std::move(oc1);
    ASSERT_EQ(oc2.x(), 1);
    ASSERT_EQ(oc2.y(), 2);
    ASSERT_EQ(oc2.z(), 3);

    ASSERT_EQ(oc1.x(), 0);
    ASSERT_EQ(oc1.y(), 0);
    ASSERT_EQ(oc1.z(), 0);
}
