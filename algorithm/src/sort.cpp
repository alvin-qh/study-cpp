#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Void _I_Swap(Int *array, UInt i, UInt j) {
    if (array[i] != array[j]) {
        array[i] ^= array[j];
        array[j] ^= array[i];
        array[i] ^= array[j];
    }
}

Void I_Shuffle(Int *array, UInt size, UInt times/* = 100*/) {
    srandom(time(null));

    for (int n = 0; n < times; ++n) {
        UInt i = random() % size;
        UInt j = random() % size;
        if (i != j) {
            _I_Swap(array, i, j);
        }
    }
}

Void I_QuickSort(Int *array, UInt size, Int(*Comp)(Int, Int)) {
    if (size <= 1) {
        return;
    }
    _I_Swap(array, random() % size, 0);

    Int i, j;
    for (i = 1, j = 0; i < size; i++) {
        if (Comp(array[0], array[i]) > 0) {
            _I_Swap(array, ++j, i);
        }
    }
    _I_Swap(array, 0, j);
    I_QuickSort(array, j, Comp);
    I_QuickSort(array + j + 1, size - j - 1, Comp);
}

bool I_IsSorted(Int *array, UInt size, Int(*Comp)(Int, Int)) {
    if (size == 2) {
        return true;
    }

    Int res = Comp(array[1], array[0]);
    for (Int i = 2, j = 1; i < size; i++, j++) {
        if (Comp(array[i], array[j]) != res) {
            return false;
        }
    }
    return true;
}