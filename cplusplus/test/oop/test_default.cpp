#include "oop/default.hpp"

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_oop_default

using namespace cpp;

/// @brief 测试默认的拷贝构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
	Point p1(10, 20);

	// 调用默认拷贝构造器
	auto p2 = p1;
	ASSERT_EQ(10, p2.x());
	ASSERT_EQ(20, p2.y());
}

/// @brief 测试默认的赋值运算符重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
	Point p1(10, 20), p2;

	// 调用默认的赋值运算符
	p2 = p1;
	ASSERT_EQ(10, p2.x());
	ASSERT_EQ(20, p2.y());
}
