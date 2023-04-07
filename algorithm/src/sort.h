#pragma once

#ifndef __SORT_H
#define __SORT_H

#include "common.h"

#include <stdlib.h>

template <typename T>
void _sort_swap(T *array, unsigned int i, unsigned int j)
{
    if (array[i] != array[j])
    {
        T tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

template <typename T>
void quick_sort(T *array, unsigned int size, int (*comp_ptr)(const T &, const T &))
{
    if (size <= 1)
    {
        return;
    }
    _sort_swap(array, random() % size, 0);

    unsigned int i, j;
    for (i = 1, j = 0; i < size; i++)
    {
        if (comp_ptr(array[0], array[i]) > 0)
        {
            _sort_swap(array, ++j, i);
        }
    }
    _sort_swap(array, 0, j);
    quick_sort(array, j, comp_ptr);
    quick_sort(array + j + 1, size - j - 1, comp_ptr);
}

template <typename T>
bool is_sorted(T *array, unsigned int size, int (*comp_ptr)(const T &, const T &))
{
    if (size == 2)
    {
        return true;
    }

    int res = comp_ptr(array[1], array[0]);
    for (unsigned int i = 2, j = 1; i < size; i++, j++)
    {
        if (comp_ptr(array[i], array[j]) != res)
        {
            return false;
        }
    }
    return true;
}

#endif //__SORT_H
