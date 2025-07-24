#include <gtest/gtest.h>

#include "test.h"
#include "sort.h"

#define TEST_SUITE_NAME test_algorithm__sort

using namespace algorithm;

/// @brief 测试快速排序函数
TEST(TEST_SUITE_NAME, quick_sort) {
    // 生成 1~10 元素的数组
    int array[10];

    // 对数组进行乱序, 确认此时数组元素无序
    int_array_shuffle(array, 10);
    ASSERT_FALSE(is_sorted(array, ARRAY_SIZE(array), &int_compare));

    // 进行快速排序, 确认排序完成后数组有序
    quick_sort(array, 10, &int_compare);
    ASSERT_TRUE(is_sorted(array, ARRAY_SIZE(array), &int_compare));
    ASSERT_LE(array[0], array[ARRAY_SIZE(array) - 1]);
}
