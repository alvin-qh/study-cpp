#include "test.h"
#include "common.h"

#include <time.h>

/**
 * 对整数进行比较
 */
int int_compare(const int &a, const int &b) {
    return a - b;
}

/**
 * 对整数数组进行填充
 */
int *int_array_fill(int *array, uint size, int start /* = 1*/) {
    for (uint i = 0; i < size; i++) array[i] = start++;

    return array;
}

/**
 * 将数组元素进行填充后乱序
 */
int *int_array_shuffle(
    int *array, uint size, int start /* = 1*/, uint times /* = 100*/) {
    if (size == 0) return array;

    // 填充数组内容
    int_array_fill(array, size, start);

    // 设置随机数种子
    srandom((uint)time(nullptr));

    // 循环若干次
    for (uint n = 0; n < times; ++n) {
        // 计算两个随机位置
        uint i = (uint)(random() % size);
        uint j = (uint)(random() % size);

        // 将两个随机位置的元素进行交换
        if (i != j) _swap(&array[i], &array[j]);
    }

    return array;
}

/**
 * 判断两个数组是否相等
 */
bool is_int_array_eq(const int *left, const int *right, uint len) {
    while (len-- > 0) {
        if (*left++ != *right++) return false;
    }
    return true;
}
