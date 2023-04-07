// 编译指令, 保持当前编译指令设定
#pragma clang diagnostic push
// 增加新的编译诊断指令, 对指定警告进行过滤
#pragma clang diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>

#include <stdlib.h>
#include <time.h>

#include "sort.h"

/**
 * 本次测试排序用的比较函数
 */
int _compare(const int &a, const int &b)
{
    return a - b;
}

/**
 * 将数组元素进行乱序
 */
template <typename T>
void _shuffle(T *array, unsigned int size, unsigned int times = 100)
{
    // 设置随机数种子
    srandom((unsigned int)time(nullptr));

    // 循环若干次
    for (unsigned int n = 0; n < times; ++n)
    {
        // 计算两个随机位置
        unsigned int i = (unsigned int)(random() % size);
        unsigned int j = (unsigned int)(random() % size);

        // 将两个随机位置的元素进行交换
        if (i != j)
            _sort_swap(array, i, j);
    }
}

/**
 * 测试快速排序函数
 */
TEST(test_sort, quick_sort)
{
    // 生成 1~10 元素的数组
    int array[10];
    for (unsigned int i = 0; i < 10; ++i)
        array[i] = i + 1;

    // 对数组进行乱序, 确认此时数组元素无序
    _shuffle(array, 10);
    EXPECT_FALSE(is_sorted(array, 10, _compare));

    // 进行快速排序, 确认排序完成后数组有序
    quick_sort(array, 10, _compare);
    EXPECT_TRUE(is_sorted(array, 10, _compare));
}

// 编译指令, 恢复之前保存的编译指令设定
#pragma clang diagnostic pop