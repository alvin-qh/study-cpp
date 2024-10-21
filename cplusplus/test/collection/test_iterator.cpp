#include "collection/iterator.hpp"

#include <vector>

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_collection_iterator

using namespace cpp::collection;

/// @brief 测试定义迭代器
TEST(TEST_SUITE_NAME, define_iterator) {
	dynamic_array<int> da{ 1, 2, 3, 4, 5 };

	int n = *da.begin();
	ASSERT_EQ(n, 1);

	// 测试正向迭代器
	for (auto it = da.begin(); it != da.end(); ++it) {
		ASSERT_EQ(*it, n++);
	}

	// 测试反向迭代器
	for (auto it = da.rbegin(); it != da.rend(); ++it) {
		ASSERT_EQ(*it, --n);
	}
}

/// @brief 测试定义只读迭代器
TEST(TEST_SUITE_NAME, define_const_iterator) {
	const dynamic_array<int> da{ 1, 2, 3, 4, 5 };

	int n = *da.begin();
	ASSERT_EQ(n, 1);

	// 测试正向迭代器
	for (auto it = da.begin(); it != da.end(); ++it) {
		ASSERT_EQ(*it, n++);
	}

	// 测试反向迭代器
	for (auto it = da.rbegin(); it != da.rend(); ++it) {
		ASSERT_EQ(*it, --n);
	}
}

/// @brief 测试通过迭代器修改被迭代对象元素
TEST(TEST_SUITE_NAME, modify_element_by_iterator) {
	dynamic_array<int> da{ 1, 2, 3, 4, 5 };

	// 测试反向迭代器
	for (auto it = da.begin(); it != da.end(); ++it) {
		// 通过迭代器修改原始元素值
		*it *= 2;
	}

	int n = *da.begin();
	ASSERT_EQ(n, 2);

	// 通过逆向迭代器确认修改的结果
	for (auto it = da.begin(); it != da.end(); ++it) {
		ASSERT_EQ(*it, n);
		n += 2;
	}
}

/// @brief 测试迭代器的随机访问
TEST(TEST_SUITE_NAME, random_access_iterator) {
	dynamic_array<int> da{ 1, 2, 3, 4, 5 };

	int n = *da.begin();
	ASSERT_EQ(n, 1);

	for (auto it = da.begin(); it <= da.end(); it += 2) {
		ASSERT_EQ(*it, n);
		n += 2;
	}

	n = *da.rbegin();
	ASSERT_EQ(n, 5);

	for (auto it = da.rbegin(); it <= da.rend(); it += 2) {
		ASSERT_EQ(*it, n);
		n -= 2;
	}
}

/// @brief 测试通过迭代器支持的 `for in` 语句
TEST(TEST_SUITE_NAME, for_in_statement) {
	dynamic_array<int> da{ 1, 2, 3, 4, 5 };

	auto it = da.begin();
	ASSERT_EQ(*it, 1);

	for (int n : da) {
		ASSERT_EQ(n, *it++);
	}
}
