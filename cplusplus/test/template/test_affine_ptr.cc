#include <gtest/gtest.h>

#include <vector>
#include <list>

#include "template/affine_ptr.h"

#define TEST_SUITE_NAME test_cplusplus__affine_ptr

using namespace std;
using namespace cxx::templated;

/// @brief 测试构建 `Box` 智能指针, 存储单值
TEST(TEST_SUITE_NAME, box_with_value) {
    Box<int> box(100);
    ASSERT_TRUE(box);
    ASSERT_EQ(*box, 100);

    *box = 200;
    ASSERT_EQ(*box, 200);
}

/// @brief 测试构建 `Box` 智能指针, 存储数组
TEST(TEST_SUITE_NAME, box_with_array) {
    Box<int> box(100, 10);
    ASSERT_TRUE(box);
    ASSERT_EQ(box.size(), 10);

    for (size_t i = 0; i < box.size(); i++) {
        ASSERT_EQ(box[i], 100);
    }

    box[0] = 200;
    box[9] = 200;
    ASSERT_EQ(box[0], 200);
    ASSERT_EQ(box[9], 200);
}

/// @brief 测试通过数组的指针构建 `Box` 智能指针
///
/// `Box` 对象中存储数组指针指向那部分数值
TEST(TEST_SUITE_NAME, box_with_array_ptr) {
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // 通过迭代器设置 `Box` 对象中存储的值
    Box<int> box = Box<int>::from_iter(static_cast<int*>(arr), static_cast<int*>(arr) + 10);
    ASSERT_TRUE(box);

    for (size_t i = 0; i < box.size(); i++) {
        ASSERT_EQ(arr[i], box[i]);
    }
}

/// @brief 测试通过向量对象迭代器构建 `Box` 智能指针
///
/// `Box` 对象中存储向量迭代器范围内的值
TEST(TEST_SUITE_NAME, box_with_vector_iter) {
    vector<int> v(10);
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = i + 1;
    }

    // 通过迭代器设置 `Box` 对象中存储的值
    Box<int> box1 = Box<int>::from_iter(v.begin(), v.end());
    ASSERT_TRUE(box1);

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

/// @brief 测试 `Box` 智能指针的对象移动
TEST(TEST_SUITE_NAME, move_instance) {
    Box<int> b1(100);

    // 调用移动构造器
    Box<int> b2 = std::move(b1);
    ASSERT_TRUE(b2);
    ASSERT_EQ(*b2, 100);
    ASSERT_FALSE(b1);

    // 调用移动赋值运算符
    b1 = std::move(b2);
    ASSERT_TRUE(b1);
    ASSERT_EQ(*b1, 100);
    ASSERT_FALSE(b2);
}
