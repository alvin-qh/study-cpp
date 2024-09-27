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

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, equal_operator_override) {
	Vector2D v2d_1(0.1, 0.2), v2d_2;
	ASSERT_FALSE(v2d_1 == v2d_2);
	ASSERT_TRUE(v2d_1 != v2d_2);

	v2d_2 = v2d_1;
	ASSERT_FALSE(v2d_1 != v2d_2);
	ASSERT_TRUE(v2d_1 == v2d_2);

	Vector3D v3d_1(0.1, 0.2, 0.3);
	ASSERT_FALSE(v3d_1 == v2d_1);
	ASSERT_TRUE(v3d_1 != v2d_1);
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

/// @brief 测试类型继承
TEST(TEST_SUITE_NAME, virtual) {
	// 当指针指向 `Vector2D` 实例时, 调用 `Vector2D::length` 方法
	const Vector2D* pv = new Vector2D(3, 4);
	ASSERT_EQ(5, pv->length());

	delete pv;

	// 当指针指向 `Vector3D` 实例时, 调用 `Vector3D::length` 方法
	pv = new Vector3D(3, 4, 8);
	ASSERT_EQ(9.4339811320566032, pv->length());

	delete pv;
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

	destroy_count = 0;

	// 当 `Vector3D` 实例被销毁后, `destroy_count` 值加 2,
	// 表示 `Vector3D` 的析构函数 以及 `Vector2D`
	// 的析构函数各执行了一次
	{
		Vector3D v;
		v.__set_destroy_count_ref(&destroy_count);
	}
	ASSERT_EQ(2, destroy_count);
}
