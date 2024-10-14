#include "template/inf_generic_param.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#define TEST_SUITE_NAME test_cplusplus_template_inf_generic_param

using namespace std;
using namespace cpp::temp;

using testing::ElementsAre;

/// @brief 定义函数, 测试可变模板参数函数 (两个参数)
/// @param a 参数 1
/// @param b 参数 2
/// @return 返回值
int _add(int a, int b) {
	return a + b;
}

/// @brief 定义仿函数, 测试可变参数模板函数 (三个参数)
///
/// @tparam T 参数类型
template<typename T>
struct Collect {
	/// @brief 重载 `()` 运算符, 定义仿函数
	/// @param a 参数 1
	/// @param b 参数 2
	/// @param c 参数 3
	/// @return 返回值
	vector<T> operator()(T a, T b, T c) const {
		vector<T> v;
		v.push_back(a);
		v.push_back(b);
		v.push_back(c);

		return v;
	}
};

/// @brief 测试可变模板参数展开为函数参数列表
TEST(TEST_SUITE_NAME, callback) {
	// 将两个模板参数展开为 `_add` 函数的参数列表
	int r1 = callback<int>(_add, 1, 2);
	ASSERT_EQ(r1, 3);

	// 将三个模板参数展开为 lambda 函数的参数列表
	double r2 = callback<double>(
		[](double a, int b, double c) { return a + b + c; },
		1.1,
		2,
		3.3
	);
	ASSERT_EQ(r2, 6.4);

	Collect<string> coll;
	// 将三个模板参数展开为 "仿函数" 的参数列表
	vector<string> r3 = callback<vector<string>>(coll, string("A"), string("B"), string("C"));
	ASSERT_EQ(r3.size(), 3);
	ASSERT_THAT(r3, ElementsAre(string("A"), string("B"), string("C")));
}

/// @brief 测试通过递归方式调用可变模板参数函数
TEST(TEST_SUITE_NAME, recursive_args) {
	// 通过对可变模板参数的递归访问参数列表
	int r1 = recursive_args(1, 2, 3, 4, 5);
	ASSERT_EQ(r1, 15);

	// 通过对可变模板参数的递归访问参数列表
	string r2 = recursive_args(string("A"), "B", "C", "D");
	ASSERT_EQ(r2, "ABCD");
}
