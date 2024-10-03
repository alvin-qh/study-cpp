#include <gtest/gtest.h>

#include "heap.h"
#include "test.h"

#define TEST_SUITE_NAME test_algorithm_heap

using namespace alg;

/// @brief 测试堆的初始化
TEST(TEST_SUITE_NAME, heap_init) {
	heap<int> h;

	// 初始化堆对象
	heap_init(h, &int_compare);

	// 确认初始化后堆的状态
	EXPECT_EQ(h.size, 0);
	EXPECT_EQ(h.capacity, DEFAULT_CAPACITY);
	EXPECT_NE(h.array, nullptr);
	EXPECT_EQ(h.comp_ptr, &int_compare);
	EXPECT_EQ(h.array[0], 0);

	// 销毁堆对象
	heap_free(h);

	// 确认销毁后堆的状态
	EXPECT_EQ(h.size, 0);
	EXPECT_EQ(h.capacity, 0);
	EXPECT_EQ(h.array, nullptr);
	EXPECT_EQ(h.comp_ptr, nullptr);
}

/// @brief 测试堆元素的存入和取出
TEST(TEST_SUITE_NAME, heap_offer) {
	heap<int> h;
	heap_init(h, &int_compare);

	// 产生测试数据
	int data[4];
	int_array_shuffle(data, ARRAY_SIZE(data), 5);

	// 将测试数据加入堆中
	for (uint i = 0; i < ARRAY_SIZE(data); i++) {
		heap_offer(h, data[i]);
	}

	// 确认添加元素后, 堆的状态, 此时堆存储区未被重建
	EXPECT_EQ(h.size, 4);
	EXPECT_EQ(h.capacity, DEFAULT_CAPACITY);

	// 继续产生测试数据
	int_array_shuffle(data, ARRAY_SIZE(data), 1);

	// 继续将测试数据加入堆中
	for (uint i = 0; i < ARRAY_SIZE(data); i++) {
		heap_offer(h, data[i]);
	}

	// 再次确认添加元素后, 堆的状态, 此时堆存储区未被重建
	EXPECT_EQ(h.size, 8);
	EXPECT_NE(h.capacity, DEFAULT_CAPACITY);

	// 确认从堆中获取元素的顺序
	for (uint i = 1; h.size > 0; i++) {
		EXPECT_EQ(heap_poll(h), i);
	}

	// 销毁堆对象
	heap_free(h);
}
