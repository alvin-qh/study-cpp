#include "oop/inherit.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_inherit

using namespace cpp;

/// @brief 测试类型继承
TEST(TEST_SUITE_NAME, inherit) {
	// 测试参数构造器
	Point3D p1(0.1, 0.2, 0.3);
	ASSERT_EQ(0.1, p1.x());
	ASSERT_EQ(0.2, p1.y());
	ASSERT_EQ(0.3, p1.z());

	// 测试拷贝构造器
	Point3D p2 = p1;
	ASSERT_EQ(0.1, p2.x());
	ASSERT_EQ(0.2, p2.y());
	ASSERT_EQ(0.3, p2.z());
}

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
	Point3D p1(0.1, 0.2, 0.3), p2;

	// 调用重载赋值运算符
	p2 = p1;
	ASSERT_EQ(0.1, p2.x());
	ASSERT_EQ(0.2, p2.y());
	ASSERT_EQ(0.3, p2.z());
}

/// @brief 测试比较运算符的重载
TEST(TEST_SUITE_NAME, equal_operator_override) {
	Point3D p1(0.1, 0.2, 0.3), p2;
	ASSERT_FALSE(p1 == p2);
	ASSERT_TRUE(p1 != p2);

	p2 = p1;
	ASSERT_TRUE(p1 == p2);
	ASSERT_FALSE(p2 != p2);

	Point2D p3(0.1, 0.2);
	ASSERT_TRUE(p1 != p3);
	ASSERT_FALSE(p1 == p3);
}

/// @brief 测试多态特性
TEST(TEST_SUITE_NAME, virtual_method) {
	// 当指针指向 `Point2D` 实例时, 调用 `Point2D::norm` 方法
	const Point2D* p = new Point2D(3, 4);
	ASSERT_EQ(5, p->norm());

	delete p;

	// 当指针指向 `Point3D` 实例时, 调用 `Point3D::norm` 方法
	p = new Point3D(3, 4, 8);
	ASSERT_EQ(9.4339811320566032, p->norm());

	delete p;
}

/// @brief 测试析构函数
TEST(TEST_SUITE_NAME, destructor) {
	uint destroy_count = 0;

	// 当 `Vector3D` 实例被销毁后, `destroy_count` 值加 2, 表示 `Vector3D`
	// 的析构函数 以及 `Vector2D` 的析构函数各执行了一次
	{
		Point3D p;
		p.__set_destroy_count_ref(&destroy_count);
	}
	ASSERT_EQ(2, destroy_count);
}
