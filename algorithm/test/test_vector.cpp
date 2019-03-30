#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <stdlib.h>
#include "vector.h"

#define ARRAY_SIZE(x) ((unsigned int)(sizeof(x) / sizeof(x[0])))

TEST (VectorTest, IV_Init) {
    I_VECTOR iv;

    iv_init(&iv);
    EXPECT_EQ(iv.size, 0);
    EXPECT_EQ(iv.capacity, VECTOR_INIT_CAP);
    EXPECT_NE(iv.array, nullptr);

    iv_free(&iv);
    EXPECT_EQ(iv.size, 0);
    EXPECT_EQ(iv.capacity, 0);
    EXPECT_EQ(iv.array, nullptr);
}

TEST(VectorTest, IV_Set_Rebuild) {
    I_VECTOR iv;
    const int values[] = {1, 2, 3, 4, 5, 6};

    iv_init(&iv);
    const void* p = iv.array;

    iv_set(&iv, values, ARRAY_SIZE(values));
    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values));
    EXPECT_EQ(iv.size, ARRAY_SIZE(values));

    for (int i = 0; i < iv.size; ++i) {
        EXPECT_EQ(iv.array[i], values[i]);
    }

    EXPECT_NE(iv.array, p);

    iv_free(&iv);
}

TEST(VectorTest, IV_Set_No_Rebuild) {
    I_VECTOR iv;
    const int values[] = {1, 2, 3, 4};

    iv_init(&iv);
    const void* p = iv.array;

    iv_set(&iv, values, ARRAY_SIZE(values));
    EXPECT_EQ(iv.capacity, VECTOR_INIT_CAP);
    EXPECT_EQ(iv.size, ARRAY_SIZE(values));

    for (int i = 0; i < iv.size; ++i) {
        EXPECT_EQ(iv.array[i], values[i]);
    }

    EXPECT_EQ(iv.array, p);

    iv_free(&iv);
}

TEST (VectorTest, IV_Add_Rebuild) {
    I_VECTOR iv;
    const int values[] = {1, 2, 3, 4, 5, 6};

    iv_init(&iv);
    const void* p = iv.array;

    iv_set(&iv, values, ARRAY_SIZE(values));

    EXPECT_EQ(iv_add(&iv, 7), ARRAY_SIZE(values) + 1);

    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values) + (unsigned int) ((ARRAY_SIZE(values) + 1) * 0.5));
    EXPECT_EQ(iv.size, ARRAY_SIZE(values) + 1);

    for (int i = 0; i < iv.size; ++i) {
        if (i < ARRAY_SIZE(values)) {
            EXPECT_EQ(iv.array[i], values[i]);
        } else {
            EXPECT_EQ(iv.array[i], 7);
        }
    }

    EXPECT_NE(iv.array, p);

    iv_free(&iv);
}

TEST (VectorTest, IV_Add_No_Rebuild) {
    I_VECTOR iv;

    iv_init(&iv);
    const void* p = iv.array;

    EXPECT_EQ(iv_add(&iv, 1), 1);
    EXPECT_EQ(iv_add(&iv, 2), 2);

    EXPECT_EQ(iv.capacity, VECTOR_INIT_CAP);
    EXPECT_EQ(iv.size, 2);
    EXPECT_EQ(iv.array[0], 1);
    EXPECT_EQ(iv.array[1], 2);

    EXPECT_EQ(iv.array, p);

    iv_free(&iv);
}

TEST (VectorTest, IV_Append_Rebuild) {
    I_VECTOR iv;
    const int values[] = {2, 3, 4, 5, 6, 7};

    iv_init(&iv);
    const void* p = iv.array;

    iv_add(&iv, 1);
    iv_append(&iv, values, ARRAY_SIZE(values));

    EXPECT_EQ(iv.size, ARRAY_SIZE(values) + 1);
    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values) + 1);
    for (int i = 0; i < iv.size; ++i) {
        if (i == 0) {
            EXPECT_EQ(iv.array[i], 1);
        } else {
            EXPECT_EQ(iv.array[i], values[i - 1]);
        }
    }

    EXPECT_NE(iv.array, p);

    iv_free(&iv);
}

TEST (VectorTest, IV_Append_No_Rebuild) {
    I_VECTOR iv;
    const int values[] = {2, 3, 4, 5};

    iv_init(&iv);
    const void* p = iv.array;

    iv_add(&iv, 1);
    iv_append(&iv, values, ARRAY_SIZE(values));

    EXPECT_EQ(iv.size, ARRAY_SIZE(values) + 1);
    EXPECT_EQ(iv.capacity, ARRAY_SIZE(values) + 1);
    for (int i = 0; i < iv.size; ++i) {
        if (i == 0) {
            EXPECT_EQ(iv.array[i], 1);
        } else {
            EXPECT_EQ(iv.array[i], values[i - 1]);
        }
    }

    EXPECT_EQ(iv.array, p);

    iv_free(&iv);
}

#pragma clang diagnostic pop