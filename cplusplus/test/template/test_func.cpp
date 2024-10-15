#include <gtest/gtest.h>

#include "template/func.hpp"
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_template_func

using namespace std;
using namespace cpp::temp;

/// @brief 测试泛型函数
TEST(TEST_SUITE_NAME, templated_function) {
	// int 类型, 调用 `template<typename T> T add(const T&, const T&)`
	ASSERT_EQ(3, add(1, 2));

	// double 类型, 调用 `template<typename T> T add(const T&, const T&)`
	ASSERT_EQ(3.3, cpp::number_to_fixed(add(1.1, 2.2), 2));

	// string 类型, 调用 `template<> string add(const string&, const string&)`
	ASSERT_EQ("Hello World", add(string("Hello"), string("World")));
}
