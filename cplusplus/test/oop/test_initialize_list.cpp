#include "oop/initialize_list.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_initialize_list

using namespace cpp::oop;

/// @brief 测试 `std::initializer_list` (列表初始化对象) 的使用
///
/// C++ 支持通过 `{}` 操作符定义初始化列表 (brace-enclosed initializer list),
/// 例如 `int a[] = { 1, 2, 3, 4, 5 };`
///
/// 如果希望自定义类型也支持通过初始化列表的语法, 则需要为类型定义一个参数构造器,
/// 且构造器参数为 `std::initializer_list` 的对象
TEST(TEST_SUITE_NAME, use_initialize_list) {
	// 实例化列表对象
	std::initializer_list<int> init_list = { 1, 2, 3, 4, 5 };

	ASSERT_EQ(init_list.size(), 5);
	ASSERT_EQ(*init_list.begin(), 1);
	ASSERT_EQ(*(init_list.end() - 1), 5);
}

/// @brief 测试通过 `std::initializer_list` (列表初始化对象)
/// 作为类构造器参数
TEST(TEST_SUITE_NAME, constructor_with_initialize_list) {
	// 调用参数构造器, 并传入 `std::initializer_list` 实例作为构造器参数
	Sequence<int> seq = { 1, 2, 3, 4, 5 };

	ASSERT_EQ(seq.size(), 5);
	ASSERT_EQ(seq[0], 1);
	ASSERT_EQ(seq[1], 2);
	ASSERT_EQ(seq[2], 3);
	ASSERT_EQ(seq[3], 4);
	ASSERT_EQ(seq[4], 5);
}
