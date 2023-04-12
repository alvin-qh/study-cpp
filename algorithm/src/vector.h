/**
 * 向量集合演示
 */
#pragma once

#ifndef __ALGORITHM_VECTOR_H
#define __ALGORITHM_VECTOR_H

#include "common.h"

#include <memory.h>

/**
 * 向量集合结构体
 */
template <class T>
struct vector
{
    // 存储元素的数组
    T *array;

    // 向量元素个数
    uint size;

    // 向量元素存储区实际长度
    uint capacity;
};

/**
 * 初始化向量结构体对象
 *
 * Args:
 *  - v: 向量结构体变量引用
 */
template <typename T>
void vector_init(vector<T> &v)
{
    // 设置初始存储区长度
    v.capacity = DEFAULT_CAPACITY;

    // 设置向量元素个数为 0
    v.size = 0;

    // 为向量存储区分配内存
    v.array = _array_alloc(v.capacity, T());
}

/**
 * 销毁向量结构体对象
 *
 * Args:
 *  - v: 向量结构体变量引用
 */
template <typename T>
void vector_free(vector<T> &v)
{
    // 释放存储区内存
    _array_free(v.array, v.capacity);

    v.array = nullptr;
    v.size = v.capacity = 0;
}

/**
 * 向向量集合中设置一组值
 *
 * Args:
 *  - v: 向量结构体变量
 *  - data: 存储要设置值的数组
 *  - len: data 数组长度
 */
template <typename T>
void vector_set(vector<T> &v, const T *data, uint len)
{
    if (!data || len == 0)
        return;

    // 若向量存储区长度不足以存储 data 数组的值, 则重新分配存储区
    if (v.capacity < len)
    {
        // 释放数组
        _array_free(v.array, v.capacity);

        // 重新分配数组
        v.array = _array_alloc(len, T());
        v.capacity = len;
    }

    // 将 data 数组元素复制到向量存储区
    _array_copy(data, v.array, len);
    v.size = len;
}

/**
 * 重建向量存储区
 *
 * Args:
 *  - array: 数组指针
 *  - size: 数组中有效元素个数
 *  - new_size: 数组新长度
 */
template <typename T>
void _vector_rebuild(vector<T> &v, uint new_capacity)
{
    // 为存储区分配内存空间
    T *new_array = _array_alloc(new_capacity, T());

    // 将向量原存储区内容复制到新内存空间中
    _array_copy(v.array, new_array, v.size);

    // 释放向量原存储空间
    _array_free(v.array, v.capacity);

    // 重设向量存储区
    v.array = new_array;
    v.capacity = new_capacity;
}

/**
 * 向向量中添加一个值
 *
 * Args:
 *  - v: 向量结构体变量
 *  - value: 要添加的值
 *
 * Return:
 *  添加后向量长度
 */
template <typename T>
uint vector_add(vector<T> &v, const T &value)
{
    // 如果向量存储区长度不够, 则重建向量存储区
    if (v.size >= v.capacity)
        _vector_rebuild(v, NEW_CAPACITY(v.capacity));

    // 在存储区末尾添加新元素值
    v.array[v.size++] = value;
    return v.size;
}

/**
 * 向向量中添加一组值
 *
 * Args:
 *  - v: 向量结构体变量
 *  - data: 要添加值的数组指针
 *  - len: data 数组的长度
 *
 * Return:
 *  添加后向量长度
 */
template <typename T>
uint vector_append(vector<T> &v, const T *data, uint len)
{
    // 判断空余空间是否足够存放, 如果不够则需重建存储空间
    if (v.capacity - v.size < len)
        _vector_rebuild(v, v.size + len);

    // 将数组内容复制到向量存储区中
    _array_copy(data, v.array + v.size, len);
    v.size += len;

    return v.size;
}

#endif // #__ALGORITHM_VECTOR_H