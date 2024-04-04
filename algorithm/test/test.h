/**
 * 测试公共部分
 */
#pragma once

#ifndef __ALGORITHM_TEST_H
#define __ALGORITHM_TEST_H

#include "common.h"

/**
 * 对整数进行比较
 *
 * Args:
 *  - `a`, `b`: 要比较的整数值
 *
 * Return:
 *  - `0` 表示 `a == b`; 负数表示 `a < b`; 正数表示 `a > b`
 */
int int_compare(const int &a, const int &b);

/**
 * 对整数数组进行填充
 *
 * Args:
 *  - `array`: 整数数组指针
 *  - `size`: 整数数组长度
 *  - `start`: 填充值的起始值
 *
 * Return:
 *  - 数组指针
 */
int *int_array_fill(int *array, uint size, int start = 1);

/**
 * 将数组元素进行填充后乱序
 *
 * Args:
 *  - `array`: 整数数组指针
 *  - `size`: 整数数组长度
 *  - `start`: 填充值的起始值
 *  - `times`: 打乱的次数
 *
 * Return:
 *  - 数组指针
 */
int *int_array_shuffle(int *array, uint size, int start = 1, uint times = 100);

/**
 * 判断两个数组是否相等
 *
 * Args:
 *  - `left`, `right`: 待比较的两个数组指针
 *  - `len`: 要比较的数组长度
 *
 * Return:
 *  - 数组是否相等
 */
bool is_int_array_eq(const int *left, const int *right, uint len);

#endif // __ALGORITHM_TEST_H
