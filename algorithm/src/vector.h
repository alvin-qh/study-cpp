#pragma once

#ifndef __VECTOR_H
#define __VECTOR_H

#include "common.h"
#include <stdlib.h>
#include <memory.h>

#define VECTOR_INIT_CAP 5
#define NEW_CAP_SIZE(oc) ((unsigned int)(oc + (oc + 1) / 2))

template <class T>
struct vector
{
    T *array;
    unsigned int size;
    unsigned int capacity;
};

template <typename T>
void vector_init(vector<T> &v)
{
    v.capacity = VECTOR_INIT_CAP;
    v.size = 0;
    v.array = (T *)malloc(sizeof(T) * v.capacity);
}

template <typename T>
void vector_free(vector<T> &v)
{
    if (v.array)
    {
        free(v.array);
        v.array = NULL;
    }
    v.size = 0;
    v.capacity = 0;
}

template <typename T>
void vector_set(vector<T> &v, const T *values, unsigned int len)
{
    if (len == 0)
    {
        return;
    }

    if (v.capacity < len)
    {
        T *op = v.array;
        v.array = (T *)malloc(sizeof(T) * len);
        v.capacity = len;
        free(op);
    }

    memcpy(v.array, values, sizeof(T) * len);
    v.size = len;
}

template <typename T>
void _vector_rebuild(vector<T> &v, unsigned int new_capacity)
{
    T *new_array = (T *)malloc(sizeof(T) * new_capacity);
    memcpy(new_array, v.array, v.size * sizeof(T));

    free(v.array);
    v.array = new_array;
    v.capacity = new_capacity;
}

template <typename T>
unsigned int vector_add(vector<T> &v, const T &value)
{
    if (v.size >= v.capacity)
    {
        _vector_rebuild(v, NEW_CAP_SIZE(v.capacity));
    }

    v.array[v.size++] = value;

    return v.size;
}

template <typename T>
unsigned int vector_append(vector<T> &v, const T *data, unsigned int len)
{
    unsigned int left = v.capacity - v.size;
    if (left < len)
    {
        _vector_rebuild(v, v.size + len);
    }

    memcpy(v.array + v.size, data, sizeof(T) * len);
    v.size += len;

    return v.size;
}

#endif // #__VECTOR_H