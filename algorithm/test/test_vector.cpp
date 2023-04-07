#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <stdlib.h>
#include "vector.h"

#define ARRAY_SIZE(x) ((unsigned int)(sizeof(x) / sizeof(x[0])))

TEST(test_vector, vector_init)
{
    vector<int> v;
    vector_init(v);

    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, VECTOR_INIT_CAP);
    EXPECT_NE(v.array, nullptr);

    vector_free(v);

    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, 0);
    EXPECT_EQ(v.array, nullptr);
}

TEST(test_vector, vector_set_with_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int *src_array = v.array;

    int data[] = {1, 2, 3, 4, 5, 6};
    vector_set(v, data, ARRAY_SIZE(data));

    EXPECT_EQ(v.capacity, ARRAY_SIZE(data));
    EXPECT_EQ(v.size, ARRAY_SIZE(data));

    for (unsigned int i = 0; i < v.size; i++)
    {
        EXPECT_EQ(v.array[i], data[i]);
    }

    EXPECT_NE(v.array, src_array);

    vector_free(v);
}

TEST(test_vector, vector_set_without_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int *src_array = v.array;

    const int data[] = {1, 2, 3, 4};
    vector_set(v, data, ARRAY_SIZE(data));

    EXPECT_EQ(v.capacity, VECTOR_INIT_CAP);
    EXPECT_EQ(v.size, ARRAY_SIZE(data));

    for (unsigned int i = 0; i < v.size; i++)
    {
        EXPECT_EQ(v.array[i], data[i]);
    }

    EXPECT_EQ(v.array, src_array);

    vector_free(v);
}

TEST(test_vector, vector_add_with_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int *src_array = v.array;

    const int data[] = {1, 2, 3, 4, 5, 6};
    vector_set(v, data, ARRAY_SIZE(data));

    EXPECT_EQ(vector_add(v, 7), ARRAY_SIZE(data) + 1);

    EXPECT_EQ(v.capacity, ARRAY_SIZE(data) + ((ARRAY_SIZE(data) + 1) / 2));
    EXPECT_EQ(v.size, ARRAY_SIZE(data) + 1);

    for (unsigned int i = 0; i < v.size; i++)
    {
        if (i < ARRAY_SIZE(data))
        {
            EXPECT_EQ(v.array[i], data[i]);
        }
        else
        {
            EXPECT_EQ(v.array[i], 7);
        }
    }

    EXPECT_NE(v.array, src_array);

    vector_free(v);
}

TEST(test_vector, vector_add_without_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int *src_array = v.array;

    EXPECT_EQ(vector_add(v, 1), 1);
    EXPECT_EQ(vector_add(v, 2), 2);

    EXPECT_EQ(v.capacity, VECTOR_INIT_CAP);
    EXPECT_EQ(v.size, 2);
    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);

    EXPECT_EQ(v.array, src_array);

    vector_free(v);
}

TEST(test_vector, vector_append_with_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int *src_array = v.array;

    int data[] = {2, 3, 4, 5, 6, 7};

    vector_add(v, 1);
    vector_append(v, data, ARRAY_SIZE(data));

    EXPECT_EQ(v.size, ARRAY_SIZE(data) + 1);
    EXPECT_EQ(v.capacity, ARRAY_SIZE(data) + 1);

    for (unsigned int i = 0; i < v.size; i++)
    {
        if (i == 0)
        {
            EXPECT_EQ(v.array[i], 1);
        }
        else
        {
            EXPECT_EQ(v.array[i], data[i - 1]);
        }
    }

    EXPECT_NE(v.array, src_array);

    vector_free(v);
}

TEST(test_vector, vector_append_without_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int *src_array = v.array;

    int data[] = {2, 3, 4, 5};

    vector_add(v, 1);
    vector_append(v, data, ARRAY_SIZE(data));

    EXPECT_EQ(v.size, ARRAY_SIZE(data) + 1);
    EXPECT_EQ(v.capacity, ARRAY_SIZE(data) + 1);

    for (unsigned int i = 0; i < v.size; i++)
    {
        if (i == 0)
        {
            EXPECT_EQ(v.array[i], 1);
        }
        else
        {
            EXPECT_EQ(v.array[i], data[i - 1]);
        }
    }

    EXPECT_EQ(v.array, src_array);

    vector_free(v);
}

#pragma clang diagnostic pop