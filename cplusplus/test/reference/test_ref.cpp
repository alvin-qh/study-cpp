#include <string>

#include "reference/ref.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_reference_ref

using namespace std;
using namespace cpp;

/// @brief 测试引用类型函数参数
TEST(TEST_SUITE_NAME, ref_arguments) {
	int a = 100, b = 200;
	cpp::swap(a, b);
	ASSERT_EQ(a, 200);
	ASSERT_EQ(b, 100);

	string s1 = "Hello", s2 = "World";
	cpp::swap(s1, s2);
	ASSERT_EQ(s1, "World");
	ASSERT_EQ(s2, "Hello");
}
