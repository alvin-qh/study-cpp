/**
 * 定义所有其他头文件所需的公共内容
 */
#pragma once

#ifndef __ALGORITHM_COMMON_H
#define __ALGORITHM_COMMON_H

#include <stdlib.h>

// 存储区初始大小常量
#define DEFAULT_CAPACITY 5

// 计算存储区扩展长度
#define NEW_CAPACITY(oc) ((uint)((oc) + ((oc) + 1) / 2))

// 计算数组长度的宏
#define ARRAY_SIZE(x) ((uint)(sizeof(x) / sizeof((x)[0])))

/**
 * 交换两个变量的值
 *
 * Args:
 *  - left_ptr, right_ptr: 要交换变量的指针
 */
template <typename T>
void _swap(T *left_ptr, T *right_ptr)
{
    // 如果两个变量不相等, 则进行交换
    if (*left_ptr != *right_ptr)
    {
        T tmp = *left_ptr;
        *left_ptr = *right_ptr;
        *right_ptr = tmp;
    }
}

/**
 * 将指定内存地址的内容复制到目标地址中
 *
 * 这里逐个进行元素复制, 主要是为了调用"拷贝构造器"
 *
 * Args:
 *  - src: 待复制的数组
 *  - dst: 复制的目标数组
 *  - len: 要复制的长度
 */
template <typename T>
void _array_copy(const T *src, T *dst, uint len)
{
    while (len-- > 0)
        // 使用 C++ operator::new 运算符, 对指定内存空间调用"拷贝构造器"
        new (dst++) T(*src++);
}

/**
 * 销毁数组, 堆数组元素进行析构, 并释放内存
 *
 * Args:
 *  - array: 待销毁的数组指针
 *  - size: 数组长度
 */
template <typename T>
void _array_free(T *array, uint size)
{
    if (array)
    {
        // 调用析构函数
        for (uint i = 0; i < size; i++)
            array[i].~T();

        // 释放内存
        free(array);
    }
}

/**
 * 分配数组
 *
 * Args:
 *  - size: 数组长度
 *
 * Return:
 *  数组指针
 */
template <typename T>
T *_array_alloc(uint size, const T &default_value)
{
    // 分配内存
    T *array = (T *)malloc(sizeof(T) * size);

    // 调用默认构造器
    for (uint i = 0; i < size; i++)
        new (&array[i]) T(default_value);

    return array;
}

/**
 * 重建向量存储区
 *
 * Args:
 *  - array: 数组指针
 *  - size: 数组中有效元素个数
 *  - new_capacity: 数组新长度
 */
template <typename T>
T *_array_rebuild(T *array, uint size, uint new_capacity)
{
    // 为存储区分配内存空间
    T *new_array = _array_alloc(new_capacity, T());

    // 将向量原存储区内容复制到新内存空间中
    _array_copy(array, new_array, size);

    // 释放向量原存储空间
    _array_free(array, size);

    return new_array;
}

#endif // __ALGORITHM_COMMON_H
