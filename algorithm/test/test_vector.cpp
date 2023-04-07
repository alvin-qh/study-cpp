// 编译指令, 保持当前编译指令设定
#pragma clang diagnostic push
// 增加新的编译诊断指令, 对指定警告进行过滤
#pragma clang diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>

#include <stdlib.h>

#include "vector.h"

// 计算数组长度的宏
#define ARRAY_SIZE(x) ((unsigned int)(sizeof(x) / sizeof((x)[0])))

/**
 * 判断两个数组是否相等
 * 
 * Args:
 *  - left, right: 待比较的两个数组指针
 * 
 * Return:
 *  len: 要比较的数组长度
*/
bool is_array_eq(const int *left, const int *right, unsigned int len)
{
    while (len-- > 0)
    {
        if (*left++ != *right++)
            return false;
    }
    return true;
}

/**
 * 测试向量集合的初始化
 */
TEST(test_vector, vector_init)
{
    vector<int> v;

    // 初始化向量集合对象
    vector_init(v);

    // 确认初始化后向量集合的状态
    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, VECTOR_INIT_CAP);
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
 *
 * 本次测试设置元素数量超出向量存储空间大小, 所以需要重建向量存储区
 */
TEST(test_vector, vector_set_with_rebuild)
{
    vector<int> v;
    vector_init(v);

    int data[] = {1, 2, 3, 4, 5, 6};
    // 设置向量元素值
    vector_set(v, data, ARRAY_SIZE(data));

    // 确认向量元素个数和存储区长度符合预期
    EXPECT_EQ(v.size, ARRAY_SIZE(data));
    EXPECT_EQ(v.capacity, ARRAY_SIZE(data));

    // 确认向量元素值符合预期
    EXPECT_TRUE(is_array_eq(data, v.array, v.size));

    vector_free(v);
}

/**
 * 测试为向量设置元素值
 *
 * 本次测试设置元素数量未超出向量存储空间大小, 所以无需重建向量存储区
 */
TEST(test_vector, vector_set_without_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int data[] = {1, 2, 3, 4};
    // 设置向量元素值
    vector_set(v, data, ARRAY_SIZE(data));

    // 确认向量元素个数和存储区长度符合预期
    EXPECT_EQ(v.capacity, VECTOR_INIT_CAP);
    EXPECT_EQ(v.size, ARRAY_SIZE(data));

    // 确认向量元素值符合预期
    EXPECT_TRUE(is_array_eq(data, v.array, v.size));

    vector_free(v);
}

/**
 * 测试为向量添加一个元素值
 *
 * 本次测试设置元素数量超出向量存储空间大小, 所以需要重建向量存储区
 */
TEST(test_vector, vector_add_with_rebuild)
{
    vector<int> v;
    vector_init(v);

    const int data[] = {1, 2, 3, 4, 5, 6};
    vector_set(v, data, ARRAY_SIZE(data));

    // 向向量中添加一个元素值, 确认向量长度增加 1
    EXPECT_EQ(vector_add(v, 7), ARRAY_SIZE(data) + 1);

    // 确认添加元素后, 向量对象的元素个数和向量存储空间长度
    EXPECT_EQ(v.capacity, ARRAY_SIZE(data) + ((ARRAY_SIZE(data) + 1) / 2));
    EXPECT_EQ(v.size, ARRAY_SIZE(data) + 1);

    // 确认向量元素
    EXPECT_TRUE(is_array_eq(v.array, data, v.size - 1));
    EXPECT_EQ(v.array[v.size - 1], 7);

    vector_free(v);
}

/**
 * 测试为向量添加一个元素值
 *
 * 本次测试设置元素数量未超出向量存储空间大小, 所以无需重建向量存储区
 */
TEST(test_vector, vector_add_without_rebuild)
{
    vector<int> v;
    vector_init(v);

    // 向向量中添加两个元素值, 确认向量长度增加 2
    EXPECT_EQ(vector_add(v, 1), 1);
    EXPECT_EQ(vector_add(v, 2), 2);

    // 确认添加元素后, 向量的元素个数以及向量存储空间长度
    EXPECT_EQ(v.size, 2);
    EXPECT_EQ(v.capacity, VECTOR_INIT_CAP);

    // 确认向量中的元素值
    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);

    vector_free(v);
}

/**
 * 测试为向量追加一组元素值
 *
 * 本次测试设置元素数量超出了向量存储空间大小, 所以需要重建向量存储区
 */
TEST(test_vector, vector_append_with_rebuild)
{
    vector<int> v;
    vector_init(v);

    int data[] = {2, 3, 4, 5, 6, 7};

    // 向向量中添加一个元素
    vector_add(v, 1);

    // 向向量中追加一组元素值
    vector_append(v, data, ARRAY_SIZE(data));

    // 确认向量元素个数和向量存储空间长度
    EXPECT_EQ(v.size, ARRAY_SIZE(data) + 1);
    EXPECT_EQ(v.capacity, ARRAY_SIZE(data) + 1);

    // 确认向量的元素值
    EXPECT_EQ(v.array[0], 1);
    EXPECT_TRUE(is_array_eq(v.array + 1, data, v.size - 1));

    vector_free(v);
}

/**
 * 测试为向量追加一组元素值
 *
 * 本次测试设置元素数量未超出向量存储空间大小, 所以无需重建向量存储区
 */
TEST(test_vector, vector_append_without_rebuild)
{
    vector<int> v;
    vector_init(v);

    int data[] = {2, 3, 4, 5};

    // 向向量中添加一个元素
    vector_add(v, 1);

    // 向向量中追加一组元素值
    vector_append(v, data, ARRAY_SIZE(data));

    // 确认向量元素个数和向量存储空间长度
    EXPECT_EQ(v.size, ARRAY_SIZE(data) + 1);
    EXPECT_EQ(v.capacity, ARRAY_SIZE(data) + 1);

    // 确认向量的元素值
    EXPECT_EQ(v.array[0], 1);
    EXPECT_TRUE(is_array_eq(v.array + 1, data, v.size - 1));

    vector_free(v);
}

// 编译指令, 恢复之前保存的编译指令设定
#pragma clang diagnostic pop