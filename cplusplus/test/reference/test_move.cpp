#include "reference/move.hpp"

#include <string>
#include <vector>
#include <utility>
#include <gtest/gtest.h>

#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_reference_move

using namespace std;
using namespace cpp;

/// @brief 测试泛型函数对泛型类型的约束
TEST(TEST_SUITE_NAME, right_reference) {
	// 通过变量将 100 作为右值接收
	int&& n1 = 100;
	ASSERT_EQ(n1, 100);

	// 将返回值作为右值返回, 相当函数的返回值转移到 `n2` 变量
	int&& n2 = return_some_one(200);
	ASSERT_EQ(n2, 200);

	int n = 300;

	// 函数返回时, 会根据变量 `n` 创建临时变量, 并移动到右值 `n3` 变量
	int&& n3 = [&n]() { return n; }();
	ASSERT_EQ(n, 300);
	ASSERT_EQ(n3, 300);

	int* pn1 = &n;
	int* pn2 = move(pn1);
	ASSERT_EQ(*pn1, n);
}

TEST(TEST_SUITE_NAME, std_move) {
	string str1 = "Hello";
	string str2 = move(str1);
	ASSERT_EQ(str1, "");
	ASSERT_EQ(str2, "Hello");

	vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(i);
	}
	vector<int> v2 = move(v1);
	ASSERT_EQ(v1.size(), 0);
	ASSERT_EQ(v2.size(), 10);
}

/// @brief 测试泛型函数对泛型类型的约束
TEST(TEST_SUITE_NAME, moveable_class) {
	// Moveable m1(1, 2, 3);
	// ASSERT_FALSE(m1.is_from_moved());

	// m1 = Moveable(4, 5, 6);
	// ASSERT_TRUE(m1.is_from_moved());

	// Moveable m2 = m1;
	// ASSERT_FALSE(m2.is_from_moved());

	// Moveable m3 = []()
	// 	{
	// 		return move(Moveable(7, 8, 9));
	// 	}();
	// ASSERT_TRUE(m3.is_from_moved());
}
