#include "oop/class.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_class

using namespace cpp;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, default_constructor) {
	Vector2D v1;
	ASSERT_EQ(0, v1.x());
	ASSERT_EQ(0, v1.y());

	// 调用默认构造器的另一种形式
	Vector2D v2 = Vector2D();
	ASSERT_EQ(0, v2.x());
	ASSERT_EQ(0, v2.y());

	// 在"堆"上调用默认构造器
	Vector2D* v3 = new Vector2D();
	ASSERT_EQ(0, v3->x());
	ASSERT_EQ(0, v3->y());

	delete v3;
}

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, arguments_constructor) {
	Vector2D v1(0.1, 0.2);
	ASSERT_EQ(0.1, v1.x());
	ASSERT_EQ(0.2, v1.y());

	Vector2D v2 = Vector2D(0.1, 0.2);
	ASSERT_EQ(0.1, v2.x());
	ASSERT_EQ(0.2, v2.y());

	// 在"堆"上调用参数构造器
	Vector2D* v3 = new Vector2D(0.1, 0.2);
	ASSERT_EQ(0.1, v3->x());
	ASSERT_EQ(0.2, v3->y());

	delete v3;
}

/// @brief 测试拷贝构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
	Vector2D v1(0.1, 0.2);

	// 调用拷贝构造器的语法格式 1
	Vector2D v2 = v1;
	ASSERT_EQ(0.1, v1.x());
	ASSERT_EQ(0.2, v1.y());

	// 调用拷贝构造器的语法格式 2
	Vector2D v3(v1);
	ASSERT_EQ(0.1, v3.x());
	ASSERT_EQ(0.2, v3.y());

	// 调用拷贝构造器的语法格式 3
	Vector2D v4 = Vector2D(v1);
	ASSERT_EQ(0.1, v3.x());
	ASSERT_EQ(0.2, v3.y());

	// 调用拷贝构造器的语法格式 3
	Vector2D* v5 = new Vector2D(v1);
	ASSERT_EQ(0.1, v3.x());
	ASSERT_EQ(0.2, v3.y());

	delete v5;
}

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
	Vector2D v1(0.1, 0.2), v2;

	// 调用重载赋值运算符
	v2 = v1;
	ASSERT_EQ(0.1, v2.x());
	ASSERT_EQ(0.2, v2.y());
}

/// @brief 测试比较运算符的重载
TEST(TEST_SUITE_NAME, equal_operator_override) {
	Vector2D v2d_1(0.1, 0.2), v2d_2;
	ASSERT_FALSE(v2d_1 == v2d_2);
	ASSERT_TRUE(v2d_1 != v2d_2);

	v2d_2 = v2d_1;
	ASSERT_FALSE(v2d_1 != v2d_2);
	ASSERT_TRUE(v2d_1 == v2d_2);
}

/// @brief 测试析构函数
TEST(TEST_SUITE_NAME, destructor) {
	uint destroy_count = 0;

	// 当 `Vector2D` 实例被销毁后, `destroy_count` 值加 1,
	// 表示 `Vector2D` 的析构函数执行了一次
	{
		Vector2D v;
		v.__set_destroy_count_ref(&destroy_count);
	}
	ASSERT_EQ(1, destroy_count);
}
