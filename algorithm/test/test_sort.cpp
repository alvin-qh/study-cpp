// 编译指令, 保持当前编译指令设定
#pragma clang diagnostic push
// 增加新的编译诊断指令, 对指定警告进行过滤
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "test.h"
#include "sort.h"

#include <gtest/gtest.h>

#include <time.h>

/**
 * 测试快速排序函数
 */
TEST(test_sort, quick_sort)
{
    // 生成 1~10 元素的数组
    int array[10];

    // 对数组进行乱序, 确认此时数组元素无序
    int_array_shuffle(array, 10);
    EXPECT_FALSE(is_sorted(array, 10, &int_compare));

    // 进行快速排序, 确认排序完成后数组有序
    quick_sort(array, 10, &int_compare);
    EXPECT_TRUE(is_sorted(array, 10, &int_compare));
}

// 编译指令, 恢复之前保存的编译指令设定
#pragma clang diagnostic pop