#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "vector.h"

#define NEW_CAP_SIZE(oc) ((unsigned int)(oc + (unsigned int)((oc + 1) * 0.5)))


void _DebugShow(I_VECTOR *pv) {
    printf("[");
    for (unsigned int i = 0; i < pv->size; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", pv->array[i]);
    }
    printf("] (size=%u, cap=%u)\n", pv->size, pv->capacity);
}

void _IV_Rebuild(I_VECTOR *pv, UInt newCap) {
    int *newArray = (int *) malloc(sizeof(Int) * newCap);
    memcpy(newArray, pv->array, pv->size * sizeof(Int));

    free(pv->array);
    pv->array = newArray;
    pv->capacity = newCap;
}

void IV_Init(I_VECTOR *pv) {
    pv->capacity = VECTOR_INIT_CAP;
    pv->size = 0;
    pv->array = (Int *) malloc(sizeof(Int) * pv->capacity);
}

void IV_Free(I_VECTOR *pv) {
    if (pv->array) {
        free(pv->array);
        pv->array = null;
    }
    pv->size = 0;
    pv->capacity = 0;
}

void IV_Set(I_VECTOR *pv, const Int *values, UInt len) {
    if (len == 0) {
        return;
    }

    if (pv->capacity < len) {
        Void *op = pv->array;
        pv->array = (Int *) malloc(sizeof(Int) * len);
        pv->capacity = len;
        free(op);
    }
    memcpy(pv->array, values, sizeof(Int) * len);
    pv->size = len;
}

UInt IV_Add(I_VECTOR *pv, Int value) {
    if (pv->size >= pv->capacity) {
        _IV_Rebuild(pv, NEW_CAP_SIZE(pv->capacity));
    }
    pv->array[pv->size++] = value;
    return pv->size;
}

UInt IV_Append(I_VECTOR *pv, const Int *value, UInt len) {
    UInt left = pv->capacity - pv->size;
    if (left < len) {
        _IV_Rebuild(pv, pv->size + len);
    }
    memcpy(pv->array + pv->size, value, sizeof(Int) * len);
    pv->size += len;

    return pv->size;
}