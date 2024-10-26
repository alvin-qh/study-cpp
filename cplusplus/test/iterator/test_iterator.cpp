#include <gtest/gtest.h>

#include <vector>

#include "iterator/dynamic_array.hpp"

#define TEST_SUITE_NAME test_cplusplus_iterator_custom

using namespace cpp::iter;

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

	// 从起始位置开始, 按步长 2 向后迭代, 被加数为迭代器对象
	for (auto it = da.begin(); it <= da.end(); it += 2) {
		ASSERT_EQ(*it, n);
		n += 2;
	}

	n = *da.rbegin();
	ASSERT_EQ(n, 5);

	// 从结束位置开始, 按步长 2 向前迭代, 被加数为迭代器对象
	for (auto it = da.rbegin(); it <= da.rend(); it += 2) {
		ASSERT_EQ(*it, n);
		n -= 2;
	}

	n = *da.begin();
	ASSERT_EQ(n, 1);

	// 从起始位置开始, 按步长 2 向后迭代
	auto it = da.begin();
	while (it < da.end()) {
		ASSERT_EQ(*it, n);

		// 被加数为 `ptrdiff_t` 数值
		it = 2 + it;
		n += 2;
	}

	n = *(da.rend() - 1);
	ASSERT_EQ(n, 1);

	// 从结束位置开始, 按步长 2 向前迭代
	auto rit = da.rend() - 1;
	while (rit >= da.rbegin()) {
		ASSERT_EQ(*rit, n);

		// 被减数为 `ptrdiff_t` 数值
		rit = 2 - rit;
		n += 2;
	}
}

/// @brief 测试通过迭代器支持的 `for in` 语句
///
/// 
TEST(TEST_SUITE_NAME, for_in_statement) {
	dynamic_array<int> da{ 1, 2, 3, 4, 5 };

	auto it = da.begin();
	ASSERT_EQ(*it, 1);

	for (int n : da) {
		ASSERT_EQ(n, *it++);
	}
}

/// @brief 测试通过 `std::iterator_traits` 工具类进行迭代器类型推断
TEST(TEST_SUITE_NAME, iterator_traits) {
	using iterator_type = dynamic_array<int>::iterator;

	ASSERT_TRUE((std::is_same_v<iterator_type, ptr_based_iterator<int>>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::difference_type, std::ptrdiff_t>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::value_type, int>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::pointer, int*>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::reference, int&>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::iterator_category, std::random_access_iterator_tag>));

	using const_iterator_type = dynamic_array<int>::const_iterator;

	ASSERT_TRUE((std::is_same_v<const_iterator_type, ptr_based_iterator<const int>>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::difference_type, std::ptrdiff_t>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::value_type, const int>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::pointer, const int*>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::reference, const int&>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::iterator_category, std::random_access_iterator_tag>));

	using reverse_iterator_type = dynamic_array<int>::reverse_iterator;

	ASSERT_TRUE((std::is_same_v<reverse_iterator_type, ptr_based_reverse_iterator<int>>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::difference_type, std::ptrdiff_t>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::value_type, int>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::pointer, int*>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::reference, int&>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::iterator_category, std::random_access_iterator_tag>));

	using const_reverse_iterator_type = dynamic_array<int>::const_reverse_iterator;

	ASSERT_TRUE((std::is_same_v<const_reverse_iterator_type, ptr_based_reverse_iterator<const int>>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::difference_type, std::ptrdiff_t>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::value_type, const int>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::pointer, const int*>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::reference, const int&>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::iterator_category, std::random_access_iterator_tag>));

	// 当使用原生指针作为迭代器类型时, 测试 `std::iterator_traits` 中定义的类型
	using pointer_iterator_type = int*;

	ASSERT_TRUE((std::is_same_v<pointer_iterator_type, int*>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::difference_type, std::ptrdiff_t>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::value_type, int>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::pointer, int*>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::reference, int&>));
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::iterator_category, std::random_access_iterator_tag>));
#if (__new_iterator)
	ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::iterator_concept, std::contiguous_iterator_tag>));
#endif
}
