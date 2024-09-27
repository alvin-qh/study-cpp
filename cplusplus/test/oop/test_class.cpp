#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "oop/class.hpp"

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_oop_class

using namespace cpp;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, default_constructor) {
	Vector2D v;
	ASSERT_EQ(0, v.x());
	ASSERT_EQ(0, v.y());
}

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, arguments_constructor) {
	Vector2D v(0.1, 0.2);
	ASSERT_EQ(0.1, v.x());
	ASSERT_EQ(0.2, v.y());
}

/// @brief 测试拷贝构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
	Vector2D v1(0.1, 0.2);

	// 调用拷贝构造器的语法格式 1
	Vector2D v2 = v1;
	ASSERT_EQ(0.1, v1.x());
	ASSERT_EQ(0.2, v1.y());

	// 调用拷贝构造器的语法格式 2
	Vector2D v3(v2);
	ASSERT_EQ(0.1, v3.x());
	ASSERT_EQ(0.2, v3.y());
}

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
	Vector2D v1(0.1, 0.2);
	Vector2D v2;

	// 调用重载赋值运算符
	v2 = v1;
	ASSERT_EQ(0.1, v2.x());
	ASSERT_EQ(0.2, v2.y());
}

/// @brief 测试类型继承
TEST(TEST_SUITE_NAME, inherit) {
	Vector3D v1(0.1, 0.2, 0.3);
	ASSERT_EQ(0.1, v1.x());
	ASSERT_EQ(0.2, v1.y());
	ASSERT_EQ(0.3, v1.z());

	Vector3D v2 = v1;
	ASSERT_EQ(0.1, v2.x());
	ASSERT_EQ(0.2, v2.y());
	ASSERT_EQ(0.3, v2.z());
}

/// @brief 测试析构函数
TEST(TEST_SUITE_NAME, destructor) {
	uint destroy_count = 0;

	{
		Vector2D v(0.1, 0.2);
		v.__set_destroy_count_ref(&destroy_count);
	}

	ASSERT_EQ(1, destroy_count);
}

#pragma clang diagnostic pop
