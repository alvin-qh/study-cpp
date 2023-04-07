#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>

#include <stdlib.h>
#include <time.h>

#include "sort.h"

void _fill(int *array, unsigned int n)
{
    for (unsigned int i = 0; i < n; ++i)
    {
        array[i] = i + 1;
    }
}

int _compare(const int &a, const int &b)
{
    return a - b;
}

template <typename T>
void _shuffle(T *array, unsigned int size, unsigned int times = 100)
{
    srandom((unsigned int)time(nullptr));

    for (int n = 0; n < times; ++n)
    {
        unsigned int i = (unsigned int)(random() % size);
        unsigned int j = (unsigned int)(random() % size);

        if (i != j)
        {
            _sort_swap(array, i, j);
        }
    }
}

TEST(test_sort, quick_sort)
{
    int array[10];
    _fill(array, 10);

    _shuffle(array, 10);
    EXPECT_FALSE(is_sorted(array, 10, _compare));

    quick_sort(array, 10, _compare);
    EXPECT_TRUE(is_sorted(array, 10, _compare));
}

#pragma clang diagnostic pop