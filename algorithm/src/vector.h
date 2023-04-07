/**
 * 向量集合演示
 */
#pragma once

#ifndef __ALGORITHM_VECTOR_H
#define __ALGORITHM_VECTOR_H

#include "common.h"

#include <memory.h>

// 向量存储区初始大小常量
#define VECTOR_INIT_CAP 5

// 计算向量存储区扩展长度
#define NEW_CAP_SIZE(oc) ((unsigned int)((oc) + ((oc) + 1) / 2))

/**
 * 向量集合结构体
 */
template <class T>
struct vector
{
    // 存储元素的数组
    T *array;

    // 向量元素个数
    unsigned int size;

    // 向量元素存储区实际长度
    unsigned int capacity;
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
    v.capacity = VECTOR_INIT_CAP;
    // 设置向量元素个数为 0
    v.size = 0;
    // 为向量存储区分配内存
    v.array = (T *)malloc(sizeof(T) * v.capacity);
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
    if (v.array)
    {
        free(v.array);
        v.array = nullptr;
    }
    v.size = v.capacity = 0;
}

/**
 * 将指定内存地址的内容复制到目标地址中
 *
 * 这里逐个进行元素复制, 主要是为了调用"拷贝构造器"
 */
template <typename T>
void _vector_copy(const T *src, T *dst, unsigned int len)
{
    while (len-- > 0)
        // 使用 C++ operator::new 运算符, 对指定内存空间调用"拷贝构造器"
        new (dst++) T(*src++);
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
void vector_set(vector<T> &v, const T *data, unsigned int len)
{
    if (!data || len == 0)
        return;

    // 若向量存储区长度不足以存储 data 数组的值, 则重新分配存储区
    if (v.capacity < len)
    {
        v.capacity = len;
        if (v.array)
            free(v.array);

        v.array = (T *)malloc(sizeof(T) * v.capacity);
    }

    // 将 data 数组元素复制到向量存储区
    _vector_copy(data, v.array, len);
    v.size = len;
}

/**
 * 重建向量存储区
 *
 * Args:
 *  - v: 向量结构体变量
 *  - new_capacity: 新的存储区长度
 */
template <typename T>
void _vector_rebuild(vector<T> &v, unsigned int new_capacity)
{
    // 为存储区分配内存空间
    T *new_array = (T *)malloc(sizeof(T) * new_capacity);

    // 将向量原存储区内容复制到新内存空间中
    _vector_copy(v.array, new_array, v.size);

    // 释放向量原存储空间
    free(v.array);

    // 向量存储空间指针指向新内存空间
    v.array = new_array;
    // 设置新的存储空间长度
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
unsigned int vector_add(vector<T> &v, const T &value)
{
    // 如果向量存储区长度不够, 则重建向量存储区
    if (v.size >= v.capacity)
        _vector_rebuild(v, NEW_CAP_SIZE(v.capacity));

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
unsigned int vector_append(vector<T> &v, const T *data, unsigned int len)
{
    // 计算向量存储区空余空间长度
    unsigned int left = v.capacity - v.size;

    // 判断空余空间是否足够存放, 如果不够则需重建存储空间
    if (left < len)
        _vector_rebuild(v, v.size + len);

    // 将数组内容复制到向量存储区中
    _vector_copy(data, v.array + v.size, len);
    v.size += len;

    return v.size;
}

#endif // #__ALGORITHM_VECTOR_H