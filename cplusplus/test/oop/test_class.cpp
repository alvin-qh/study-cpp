#include "oop/class.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_class

using namespace cpp;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, default_constructor) {
	Point2D p1;
	ASSERT_EQ(0, p1.x());
	ASSERT_EQ(0, p1.y());

	// 调用默认构造器的另一种形式
	Point2D p2 = Point2D();
	ASSERT_EQ(0, p2.x());
	ASSERT_EQ(0, p2.y());

	// 在"堆"上调用默认构造器
	Point2D* p3 = new Point2D();
	ASSERT_EQ(0, p3->x());
	ASSERT_EQ(0, p3->y());

	delete p3;
}

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, arguments_constructor) {
	Point2D p1(0.1, 0.2);
	ASSERT_EQ(0.1, p1.x());
	ASSERT_EQ(0.2, p1.y());

	Point2D p2 = Point2D(0.1, 0.2);
	ASSERT_EQ(0.1, p2.x());
	ASSERT_EQ(0.2, p2.y());

	// 在"堆"上调用参数构造器
	Point2D* p3 = new Point2D(0.1, 0.2);
	ASSERT_EQ(0.1, p3->x());
	ASSERT_EQ(0.2, p3->y());

	delete p3;
}

/// @brief 测试拷贝构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
	Point2D p1(0.1, 0.2);

	// 调用拷贝构造器的语法格式 1
	Point2D p2 = p1;
	ASSERT_EQ(0.1, p1.x());
	ASSERT_EQ(0.2, p1.y());

	// 调用拷贝构造器的语法格式 2
	Point2D p3(p1);
	ASSERT_EQ(0.1, p3.x());
	ASSERT_EQ(0.2, p3.y());

	// 调用拷贝构造器的语法格式 3
	Point2D p4 = Point2D(p1);
	ASSERT_EQ(0.1, p4.x());
	ASSERT_EQ(0.2, p4.y());

	// 调用拷贝构造器的语法格式 3
	Point2D* p5 = new Point2D(p1);
	ASSERT_EQ(0.1, p5->x());
	ASSERT_EQ(0.2, p5->y());

	delete p5;
}

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
	Point2D p1(0.1, 0.2), p2;

	// 调用重载赋值运算符
	p2 = p1;
	ASSERT_EQ(0.1, p2.x());
	ASSERT_EQ(0.2, p2.y());
}

/// @brief 测试比较运算符的重载
TEST(TEST_SUITE_NAME, equal_operator_override) {
	Point2D p1(0.1, 0.2), p2;
	ASSERT_FALSE(p1 == p2);
	ASSERT_TRUE(p1 != p2);

	p2 = p1;
	ASSERT_FALSE(p1 != p2);
	ASSERT_TRUE(p1 == p2);
}

/// @brief 测试析构函数
TEST(TEST_SUITE_NAME, destructor) {
	uint destroy_count = 0;

	// 当 `Point2D` 实例被销毁后, `destroy_count` 值加 1,
	// 表示 `Point2D` 的析构函数执行了一次
	{
		Point2D p;
		p.__set_destroy_count_ref(&destroy_count);
	}
	ASSERT_EQ(1, destroy_count);
}
