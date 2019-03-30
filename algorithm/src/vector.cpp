#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "vector.h"

#define NEW_CAP_SIZE(oc) ((unsigned int)(oc + (unsigned int)((oc + 1) * 0.5)))


void _debug_show(I_VECTOR *pv) {
    printf("[");
    for (unsigned int i = 0; i < pv->size; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", pv->array[i]);
    }
    printf("] (size=%u, cap=%u)\n", pv->size, pv->capacity);
}

void _iv_rebuild(I_VECTOR *pv, unsigned int newCap) {
    int *newArray = (int *) malloc(sizeof(int) * newCap);
    memcpy(newArray, pv->array, pv->size * sizeof(int));

    free(pv->array);
    pv->array = newArray;
    pv->capacity = newCap;
}

void iv_init(I_VECTOR *pv) {
    pv->capacity = VECTOR_INIT_CAP;
    pv->size = 0;
    pv->array = (int *) malloc(sizeof(int) * pv->capacity);
}

void iv_free(I_VECTOR *pv) {
    if (pv->array) {
        free(pv->array);
        pv->array = nullptr;
    }
    pv->size = 0;
    pv->capacity = 0;
}

void iv_set(I_VECTOR *pv, const int *values, unsigned int len) {
    if (len == 0) {
        return;
    }

    if (pv->capacity < len) {
        void *op = pv->array;
        pv->array = (int *) malloc(sizeof(int) * len);
        pv->capacity = len;
        free(op);
    }
    memcpy(pv->array, values, sizeof(int) * len);
    pv->size = len;
}

unsigned int iv_add(I_VECTOR *pv, int value) {
    if (pv->size >= pv->capacity) {
        _iv_rebuild(pv, NEW_CAP_SIZE(pv->capacity));
    }
    pv->array[pv->size++] = value;
    return pv->size;
}

unsigned int iv_append(I_VECTOR *pv, const int *value, unsigned int len) {
    unsigned int left = pv->capacity - pv->size;
    if (left < len) {
        _iv_rebuild(pv, pv->size + len);
    }
    memcpy(pv->array + pv->size, value, sizeof(int) * len);
    pv->size += len;

    return pv->size;
}