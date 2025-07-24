#include <gtest/gtest.h>

#include "test.h"
#include "heap.h"

#define TEST_SUITE_NAME test_algorithm__heap

using namespace algorithm;

/// @brief 测试堆的初始化
TEST(TEST_SUITE_NAME, heap_init) {
    heap<int> h;

    // 初始化堆对象
    heap_init(h, &int_compare);

    // 确认初始化后堆的状态
    ASSERT_EQ(h.size, 0);
    ASSERT_EQ(h.capacity, DEFAULT_CAPACITY);
    ASSERT_NE(h.array, nullptr);
    ASSERT_EQ(h.comp_ptr, &int_compare);
    ASSERT_EQ(h.array[0], 0);

    // 销毁堆对象
    heap_free(h);

    // 确认销毁后堆的状态
    ASSERT_EQ(h.size, 0);
    ASSERT_EQ(h.capacity, 0);
    ASSERT_EQ(h.array, nullptr);
    ASSERT_EQ(h.comp_ptr, nullptr);
}

/// @brief 测试堆元素的存入和取出
TEST(TEST_SUITE_NAME, heap_offer) {
    heap<int> h;
    heap_init(h, &int_compare);

    // 产生测试数据
    int data[4];
    int_array_shuffle(data, ARRAY_SIZE(data), 5);

    // 将测试数据加入堆中
    for (size_t i = 0; i < ARRAY_SIZE(data); i++) {
        heap_offer(h, data[i]);
    }

    // 确认添加元素后, 堆的状态, 此时堆存储区未被重建
    ASSERT_EQ(h.size, 4);
    ASSERT_EQ(h.capacity, DEFAULT_CAPACITY);

    // 继续产生测试数据
    int_array_shuffle(data, ARRAY_SIZE(data), 1);

    // 继续将测试数据加入堆中
    for (size_t i = 0; i < ARRAY_SIZE(data); i++) {
        heap_offer(h, data[i]);
    }

    // 再次确认添加元素后, 堆的状态, 此时堆存储区未被重建
    ASSERT_EQ(h.size, 8);
    ASSERT_NE(h.capacity, DEFAULT_CAPACITY);

    // 确认从堆中获取元素的顺序
    for (size_t i = 1; h.size > 0; i++) {
        ASSERT_EQ(heap_poll(h), i);
    }

    // 销毁堆对象
    heap_free(h);
}
