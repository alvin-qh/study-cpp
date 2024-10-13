#include "oop/operator.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_operator

using namespace cpp::oop;

/// @brief 测试加法运算符重载, 将两个对象相加
TEST(TEST_SUITE_NAME, operator_plus) {
	Operator o1(1, 2, 3), o2(10, 20, 30);

	Operator r = o1 + o2;
	ASSERT_EQ(r.x(), 11);
	ASSERT_EQ(r.y(), 22);
	ASSERT_EQ(r.z(), 33);
}

/// @brief 测试减法运算符重载, 将两个对象相减
///
/// 该减法运算符重载是通过 `Operator` 类型的友元函数完成
TEST(TEST_SUITE_NAME, operator_minus) {
	Operator o1(1, 2, 3), o2(10, 20, 30);

	Operator r = o1 - o2;
	ASSERT_EQ(r.x(), -9);
	ASSERT_EQ(r.y(), -18);
	ASSERT_EQ(r.z(), -27);
}

/// @brief 测试下标操作符重载, 获取指定变量值
TEST(TEST_SUITE_NAME, operator_index) {
	Operator o(1, 2, 3);

	ASSERT_EQ(o[0], 1);
	ASSERT_EQ(o[1], 2);
	ASSERT_EQ(o[2], 3);
}

/// @brief 测试乘法运算符重载, 将当前对象和一个浮点数相乘
TEST(TEST_SUITE_NAME, operator_times_to_double) {
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
TEST(TEST_SUITE_NAME, operator_times_to_object) {
	Operator o1(1, 2, 3), o2(10, 20, 30);

	double r = o1 * o2;
	ASSERT_EQ(r, 140);
}
