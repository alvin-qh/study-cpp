#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "sort.h"
#include "test.h"

#include <gtest/gtest.h>

/**
 * 测试快速排序函数
 */
TEST(test_algorithm_sort, quick_sort) {
	// 生成 1~10 元素的数组
	int array[10];

	// 对数组进行乱序, 确认此时数组元素无序
	alg::int_array_shuffle(array, 10);
	EXPECT_FALSE(alg::is_sorted(array, ARRAY_SIZE(array), &alg::int_compare));

	// 进行快速排序, 确认排序完成后数组有序
	alg::quick_sort(array, 10, &alg::int_compare);
	EXPECT_TRUE(alg::is_sorted(array, ARRAY_SIZE(array), &alg::int_compare));
	EXPECT_LE(array[0], array[ARRAY_SIZE(array) - 1]);
}

#pragma clang diagnostic pop
