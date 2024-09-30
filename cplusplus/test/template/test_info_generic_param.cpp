#include "template/inf_generic_param.hpp"

#include <string>

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_template_inf_generic_param

using namespace std;
using namespace cpp;

/// @brief 测试通过递归方式调用不定模板参数函数
TEST(TEST_SUITE_NAME, recursive_args) {
	int r1 = recursive_args(1, 2, 3, 4, 5);
	ASSERT_EQ(r1, 15);

	string r2 = recursive_args(string("A"), "B", "C", "D");
	ASSERT_EQ(r2, "ABCD");
}
