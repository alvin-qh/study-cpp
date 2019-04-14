#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <stdlib.h>
#include "sort.h"

Void _I_Debug_Show(Int* array, UInt n) {
    printf("[");
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", array[i]);
    }
    printf("]\n");
}

Void _I_FillNum(Int *array, UInt n) {
    for (UInt i = 0; i < n; ++i) {
        array[i] = i + 1;
    }
}

Int _I_Comp(Int a, Int b) {
    return a - b;
}

TEST (SortTest, I_QuickSort) {
    Int array[10];
    _I_FillNum(array, 10);

    I_Shuffle(array, 10);
    EXPECT_FALSE(I_IsSorted(array, 10, _I_Comp));

    I_QuickSort(array, 10, _I_Comp);
    EXPECT_TRUE(I_IsSorted(array, 10, _I_Comp));
}

#pragma clang diagnostic pop