#ifndef __VECTOR_H
#define __VECTOR_H

#include "common.h"

#define VECTOR_INIT_CAP 5

typedef struct _I_VECTOR {
    Int *array;
    UInt size;
    UInt capacity;
} I_VECTOR;

extern "C" {

void IV_Init(I_VECTOR *pv);

void IV_Free(I_VECTOR *pv);

void IV_Set(I_VECTOR *pv, const Int *values, UInt len);

unsigned int IV_Add(I_VECTOR *pv, Int value);

unsigned int IV_Append(I_VECTOR *pv, const Int *value, UInt len);

}


#endif  // #__VECTOR_H