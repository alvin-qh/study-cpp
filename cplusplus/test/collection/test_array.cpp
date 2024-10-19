#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>

#define TEST_SUITE_NAME test_cplusplus_collection_array

using namespace std;
using testing::ElementsAre;

/// @brief 测试创建 `array` 对象实例
TEST(TEST_SUITE_NAME, create_array) {
	// 创建长度为 5, 元素未初始化的 `array` 对象
	array<int, 5> arr;

	ASSERT_EQ(arr.size(), 5);
	ASSERT_THAT(arr, ElementsAre(0, 0, 0, 0, 0));
}

TEST(TEST_SUITE_NAME, test_array_at) {
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto arr = to_array(a);
}
