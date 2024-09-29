#include "oop/affine_ptr.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <list>

#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_affine_ptr

using namespace std;
using namespace cpp;

/// @brief 测试构建智能指针
TEST(TEST_SUITE_NAME, box_with_value) {
	Box<int> box(100);
	ASSERT_EQ(*box, 100);

	*box = 200;
	ASSERT_EQ(*box, 200);
}

TEST(TEST_SUITE_NAME, box_with_array) {
	Box<int> box(100, 10);
	ASSERT_EQ(box.size(), 10);

	for (size_t i = 0; i < box.size(); i++) {
		ASSERT_EQ(box[i], 100);
	}

	box[0] = 200;
	box[9] = 200;
	ASSERT_EQ(box[0], 200);
	ASSERT_EQ(box[9], 200);
}

TEST(TEST_SUITE_NAME, box_with_array_ptr) {
	int* arr = new int[10];
	for (size_t i = 0; i < 10; i++) {
		arr[i] = i + 1;
	}

	Box<int> box = Box<int>::from_iter(arr, arr + 10);
	for (size_t i = 0; i < box.size(); i++) {
		ASSERT_EQ(*(arr + i), box[i]);
	}

	delete[] arr;
}

TEST(TEST_SUITE_NAME, box_with_vector_iter) {
	vector<int> v(10);
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = i + 1;
	}

	Box<int> box1 = Box<int>::from_iter(v.begin(), v.end());
	for (size_t i = 0; i < box1.size(); i++) {
		ASSERT_EQ(v[i], box1[i]);
	}

	// 因为链表不是连续空间, 故链表的迭代器
	list<int> l;
	for (size_t i = 0; i < 10; i++) {
		l.push_back(i + 1);
	}

	vector<int> v2(l.begin(), l.end());
}
