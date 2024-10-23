#include <gtest/gtest.h>

#include "oop/default.hpp"

#define TEST_SUITE_NAME test_cplusplus_oop_default

using namespace cpp::oop;

/// @brief 测试默认的拷贝构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
	Default d1("d1");

	// 调用默认拷贝构造器
	auto d2 = d1;
	ASSERT_STREQ("d1", d2.name().c_str());
}

/// @brief 测试默认的赋值运算符重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
	Default d1("d1"), d2;

	// 调用默认的赋值运算符
	d2 = d1;
	ASSERT_EQ("d1", d2.name());
}
