// 编译指令, 保持当前编译指令设定
#pragma clang diagnostic push
// 增加新的编译诊断指令, 对指定警告进行过滤
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "test.h"
#include "vector.h"

#include <gtest/gtest.h>

/**
 * 测试向量集合的初始化
 */
TEST(test_vector, vector_init) {
    vector<int> v;

    // 初始化向量集合对象
    vector_init(v);

    // 确认初始化后向量集合的状态
    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, DEFAULT_CAPACITY);
    EXPECT_NE(v.array, nullptr);

    // 销毁向量集合对象
    vector_free(v);

    // 确认销毁后向量集合的状态
    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, 0);
    EXPECT_EQ(v.array, nullptr);
}

/**
 * 测试为向量设置元素值
 */
TEST(test_vector, vector_set) {
    vector<int> v;
    vector_init(v);

    // 设置向量元素值
    int data1[] = {1, 2, 3, 4};
    vector_set(v, data1, ARRAY_SIZE(data1));

    // 确认向量元素符合预期, 且未重建存储区
    EXPECT_EQ(v.size, ARRAY_SIZE(data1));
    EXPECT_EQ(v.capacity, DEFAULT_CAPACITY);
    EXPECT_TRUE(is_int_array_eq(data1, v.array, v.size));

    // 再次设置向量元素值
    int data2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    vector_set(v, data2, ARRAY_SIZE(data2));

    // 确认向量元素符合预期, 且重建了存储区
    EXPECT_EQ(v.size, ARRAY_SIZE(data2));
    EXPECT_NE(v.capacity, DEFAULT_CAPACITY);
    EXPECT_TRUE(is_int_array_eq(data2, v.array, v.size));

    vector_free(v);
}

/**
 * 测试为向量添加一个元素值
 */
TEST(test_vector, vector_add) {
    vector<int> v;
    vector_init(v);

    // 向向量中添加一个元素值, 确认向量长度增加 4
    EXPECT_EQ(vector_add(v, 1), 1);
    EXPECT_EQ(vector_add(v, 2), 2);
    EXPECT_EQ(vector_add(v, 3), 3);
    EXPECT_EQ(vector_add(v, 4), 4);

    // 确认添加元素后, 向量对象的元素个数和向量存储空间长度, 未重建存储区
    EXPECT_EQ(v.capacity, DEFAULT_CAPACITY);
    EXPECT_EQ(v.size, 4);

    // 继续向向量中添加一个元素值, 确认向量长度增加 4
    EXPECT_EQ(vector_add(v, 5), 5);
    EXPECT_EQ(vector_add(v, 6), 6);
    EXPECT_EQ(vector_add(v, 7), 7);
    EXPECT_EQ(vector_add(v, 8), 8);

    // 确认添加元素后, 向量对象的元素个数和向量存储空间长度, 已重建存储区
    EXPECT_NE(v.capacity, DEFAULT_CAPACITY);
    EXPECT_EQ(v.size, 8);

    // 确认向量中元素符合预期
    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);
    EXPECT_EQ(v.array[2], 3);
    EXPECT_EQ(v.array[3], 4);
    EXPECT_EQ(v.array[4], 5);
    EXPECT_EQ(v.array[5], 6);
    EXPECT_EQ(v.array[6], 7);
    EXPECT_EQ(v.array[7], 8);

    vector_free(v);
}

/**
 * 测试为向量追加一组元素值
 */
TEST(test_vector, vector_append) {
    vector<int> v;
    vector_init(v);

    int data[] = {1, 2, 3, 4};

    // 向向量中追加一组元素值, 此次无须重建存储区
    vector_append(v, data, ARRAY_SIZE(data));

    // 确认向量中包含的元素, 以及向量存储区未被重建
    EXPECT_EQ(v.capacity, DEFAULT_CAPACITY);
    EXPECT_EQ(v.size, ARRAY_SIZE(data));
    EXPECT_TRUE(is_int_array_eq(data, v.array, ARRAY_SIZE(data)));

    int_array_fill(data, ARRAY_SIZE(data), 5);

    // 向向量中追加一组元素值, 此次需重建存储区
    vector_append(v, data, ARRAY_SIZE(data));

    // 确认向量中包含的元素, 以及向量存储区被重建
    EXPECT_NE(v.capacity, DEFAULT_CAPACITY);
    EXPECT_EQ(v.size, ARRAY_SIZE(data) + 4);
    EXPECT_TRUE(is_int_array_eq(data, v.array + 4, ARRAY_SIZE(data)));

    vector_free(v);
}

// 编译指令, 恢复之前保存的编译指令设定
#pragma clang diagnostic pop
