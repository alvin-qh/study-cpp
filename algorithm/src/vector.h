#ifndef __VECTOR_H
#define __VECTOR_H

#define VECTOR_INIT_CAP 5

typedef struct _I_VECTOR {
    int *array;
    unsigned int size;
    unsigned int capacity;
} I_VECTOR;

extern "C" {

void iv_init(I_VECTOR *pv);

void iv_free(I_VECTOR *pv);

void iv_set(I_VECTOR *pv, const int *values, unsigned int len);

unsigned int iv_add(I_VECTOR *pv, int value);

unsigned int iv_append(I_VECTOR *pv, const int *value, unsigned int len);

}


#endif