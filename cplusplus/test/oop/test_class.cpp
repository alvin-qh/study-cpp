#include "oop/class.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_class

using namespace cpp::oop;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, default_constructor) {
	AClass c1;
	ASSERT_EQ(0, c1.value());

	// 调用默认构造器的另一种形式
	AClass c2 = AClass();
	ASSERT_EQ(0, c2.value());

	// 在"堆"上调用默认构造器
	AClass* pc = new AClass();
	ASSERT_EQ(0, pc->value());

	delete pc;
}

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, arguments_constructor) {
	AClass c1(100);
	ASSERT_EQ(100, c1.value());

	AClass c2 = AClass(100);
	ASSERT_EQ(100, c2.value());

	// 在"堆"上调用参数构造器
	AClass* p3 = new AClass(100);
	ASSERT_EQ(100, p3->value());

	delete p3;
}

/// @brief 测试拷贝构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
	AClass c1(100);

	// 调用拷贝构造器的语法格式 1
	AClass c2 = c1;
	ASSERT_EQ(100, c1.value());

	// 调用拷贝构造器的语法格式 2
	AClass c3(c1);
	ASSERT_EQ(100, c3.value());

	// 调用拷贝构造器的语法格式 3
	AClass p4 = AClass(c1);
	ASSERT_EQ(1o0, p4.value());

	// 调用拷贝构造器的语法格式 3
	AClass* pc = new AClass(c1);
	ASSERT_EQ(100, pc->value());

	delete pc;
}

/// @brief 测试赋值运算符的重载
TEST(TEST_SUITE_NAME, assign_operator_override) {
	AClass c1(100), c2;

	// 调用重载赋值运算符
	c2 = c1;
	ASSERT_EQ(100, c2.value());
}

/// @brief 测试比较运算符的重载
TEST(TEST_SUITE_NAME, equal_operator_override) {
	Point2D c1(100), c2;
	ASSERT_FALSE(c1 == c2);
	ASSERT_TRUE(c1 != c2);

	c2 = c1;
	ASSERT_FALSE(c1 != c2);
	ASSERT_TRUE(c1 == c2);
}

/// @brief 测试析构函数
TEST(TEST_SUITE_NAME, destructor) {
	uint32_t destroy_count = 0;

	// 当 `Point2D` 实例被销毁后, `destroy_count` 值加 1,
	// 表示 `Point2D` 的析构函数执行了一次
	{
		AClass c;
		c.__set_destroy_count_ref(&destroy_count);
	}
	ASSERT_EQ(1, destroy_count);
}
