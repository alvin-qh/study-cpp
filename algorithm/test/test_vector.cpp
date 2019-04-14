#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <stdlib.h>
#include "vector.h"

#define ARRAY_SIZE(x) ((UInt)(sizeof(x) / sizeof(x[0])))

TEST (VectorTest, IV_Init) {
    I_VECTOR iv;

    IV_Init(&iv);
    EXPECT_EQ(iv.size, 0);
    EXPECT_EQ(iv.capacity, VECTOR_INIT_CAP);
    EXPECT_NE(iv.array, null);

    IV_Free(&iv);
    EXPECT_EQ(iv.size, 0);
    EXPECT_EQ(iv.capacity, 0);
    EXPECT_EQ(iv.array, null);
}

TEST(VectorTest, IV_Set_Rebuild) {
    I_VECTOR iv;
    const Int values[] = {1, 2, 3, 4, 5, 6};

    IV_Init(&iv);
    const Void *p = iv.array;

    IV_Set(&iv, values, ARRAY_SIZE(values));
    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values));
    EXPECT_EQ(iv.size, ARRAY_SIZE(values));

    for (Int i = 0; i < iv.size; ++i) {
        EXPECT_EQ(iv.array[i], values[i]);
    }

    EXPECT_NE(iv.array, p);

    IV_Free(&iv);
}

TEST(VectorTest, IV_Set_No_Rebuild) {
    I_VECTOR iv;
    const Int values[] = {1, 2, 3, 4};

    IV_Init(&iv);
    const Void *p = iv.array;

    IV_Set(&iv, values, ARRAY_SIZE(values));
    EXPECT_EQ(iv.capacity, VECTOR_INIT_CAP);
    EXPECT_EQ(iv.size, ARRAY_SIZE(values));

    for (Int i = 0; i < iv.size; ++i) {
        EXPECT_EQ(iv.array[i], values[i]);
    }

    EXPECT_EQ(iv.array, p);

    IV_Free(&iv);
}

TEST (VectorTest, IV_Add_Rebuild) {
    I_VECTOR iv;
    const Int values[] = {1, 2, 3, 4, 5, 6};

    IV_Init(&iv);
    const Void *p = iv.array;

    IV_Set(&iv, values, ARRAY_SIZE(values));

    EXPECT_EQ(IV_Add(&iv, 7), ARRAY_SIZE(values) + 1);

    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values) + (UInt) ((ARRAY_SIZE(values) + 1) * 0.5));
    EXPECT_EQ(iv.size, ARRAY_SIZE(values) + 1);

    for (Int i = 0; i < iv.size; ++i) {
        if (i < ARRAY_SIZE(values)) {
            EXPECT_EQ(iv.array[i], values[i]);
        } else {
            EXPECT_EQ(iv.array[i], 7);
        }
    }

    EXPECT_NE(iv.array, p);

    IV_Free(&iv);
}

TEST (VectorTest, IV_Add_No_Rebuild) {
    I_VECTOR iv;

    IV_Init(&iv);
    const Void *p = iv.array;

    EXPECT_EQ(IV_Add(&iv, 1), 1);
    EXPECT_EQ(IV_Add(&iv, 2), 2);

    EXPECT_EQ(iv.capacity, VECTOR_INIT_CAP);
    EXPECT_EQ(iv.size, 2);
    EXPECT_EQ(iv.array[0], 1);
    EXPECT_EQ(iv.array[1], 2);

    EXPECT_EQ(iv.array, p);

    IV_Free(&iv);
}

TEST (VectorTest, IV_Append_Rebuild) {
    I_VECTOR iv;
    const Int values[] = {2, 3, 4, 5, 6, 7};

    IV_Init(&iv);
    const Void *p = iv.array;

    IV_Add(&iv, 1);
    IV_Append(&iv, values, ARRAY_SIZE(values));

    EXPECT_EQ(iv.size, ARRAY_SIZE(values) + 1);
    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values) + 1);
    for (Int i = 0; i < iv.size; ++i) {
        if (i == 0) {
            EXPECT_EQ(iv.array[i], 1);
        } else {
            EXPECT_EQ(iv.array[i], values[i - 1]);
        }
    }

    EXPECT_NE(iv.array, p);

    IV_Free(&iv);
}

TEST (VectorTest, IV_Append_No_Rebuild) {
    I_VECTOR iv;
    const Int values[] = {2, 3, 4, 5};

    IV_Init(&iv);
    const Void *p = iv.array;

    IV_Add(&iv, 1);
    IV_Append(&iv, values, ARRAY_SIZE(values));

    EXPECT_EQ(iv.size, ARRAY_SIZE(values) + 1);
    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values) + 1);
    for (Int i = 0; i < iv.size; ++i) {
        if (i == 0) {
            EXPECT_EQ(iv.array[i], 1);
        } else {
            EXPECT_EQ(iv.array[i], values[i - 1]);
        }
    }

    EXPECT_EQ(iv.array, p);

    IV_Free(&iv);
}

TEST (VectorTest, AA) {
    int a = 1, b = 2;

    a ^= b;
    b ^= a;
    a ^= b;
    printf("%d, %d\n", a, b);
}

#pragma clang diagnostic pop