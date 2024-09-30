#include "template/inf_generic_param.hpp"

#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_template_inf_generic_param

using namespace std;
using namespace cpp;

int _add(int a, int b) {
	return a + b;
}

template<typename T>
struct Combine {
	vector<T> operator()(T a, T b, T c) const {
		vector<T> v;
		v.push_back(a);
		v.push_back(b);
		v.push_back(c);

		return v;
	}
};


/// @brief 测试通过递归方式调用不定模板参数函数
TEST(TEST_SUITE_NAME, callback) {
	int r1 = callback<int>(_add, 1, 2);
	ASSERT_EQ(r1, 3);

	double r2 = callback<double>(
		[](double a, int b, double c) { return a + b; },
		1.1,
		2,
		3.3
	);
	ASSERT_EQ(r2, 3.1);
}

/// @brief 测试通过递归方式调用不定模板参数函数
TEST(TEST_SUITE_NAME, recursive_args) {
	int r1 = recursive_args(1, 2, 3, 4, 5);
	ASSERT_EQ(r1, 15);

	string r2 = recursive_args(string("A"), "B", "C", "D");
	ASSERT_EQ(r2, "ABCD");
}
