#ifndef __SORT_H
#define __SORT_H

#include "common.h"

Void I_Shuffle(Int *array, UInt size, UInt times = 100);

Void I_QuickSort(Int *array, UInt size, Int(*Comp)(Int, Int));

bool I_IsSorted(Int *array, UInt size, Int(*Comp)(Int, Int));

#endif //__SORT_H
