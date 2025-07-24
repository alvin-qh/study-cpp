#include <gtest/gtest.h>

#include <memory>

#include "large_object.h"

#define TEST_SUITE_NAME test_cplusplus_ptr__weak_ptr

using namespace std;
using namespace cxx::pointer;

/// @brief 测试创建 `weak_ptr` 智能指针
///
/// `weak_ptr` 实例需要通过 `shared_ptr` 实例来创建, `weak_ptr` 实例不会持有 `shared_ptr`
/// 实例的引用计数, 故不会影响到 `shared_ptr` 的资源回收
///
/// 当所关联的 `shared_ptr` 释放了相关资源后, `weak_ptr` 实例就会变为无效
///
/// `weak_ptr` 实例必须通过 `weak_ptr::lock` 方法转为 `shared_ptr` 实例后,
/// 才能对其托管的资源进行访问, 转为 `shared_ptr` 的同时, 会增加引用计数
///
/// `weak_ptr` 也具备 `weak_ptr::use_count` 方法, 但获取的是其相关联的 `shared_ptr`
/// 实例的引用计数值
TEST(TEST_SUITE_NAME, make_weak_ptr) {
    // 通过 `make_shared` 函数创建实例
    shared_ptr<LargeObject<int, 10>> s_ptr_1 = make_shared<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // 通过 `shared_ptr` 实例创建 `weak_ptr` 实例, 此时不会增加 `shared_ptr` 实例的引用计数
    weak_ptr<LargeObject<int, 10>> w_ptr = s_ptr_1;
    ASSERT_EQ(s_ptr_1.use_count(), 1);
    ASSERT_EQ(w_ptr.use_count(), 1); // `weak_ptr::use_count` 返回的是其关联 `shared_ptr` 实例的引用计数
    ASSERT_FALSE(w_ptr.expired()); // `weak_ptr::expired` 方法返回其关联的 `shared_ptr` 是否有效

    // 通过 `weak_ptr::lock` 方法获取关联的 `shared_ptr` 实例, 此时会增加引用计数
    shared_ptr<LargeObject<int, 10>> s_ptr_2 = w_ptr.lock();
    ASSERT_EQ(s_ptr_1.use_count(), 2);
    ASSERT_EQ(s_ptr_2.use_count(), 2);
    ASSERT_EQ(w_ptr.use_count(), 2);
    ASSERT_FALSE(w_ptr.expired());

    // 释放一个 `shared_ptr`, 由于引用计数不为 `0`, 故未释放资源
    s_ptr_1.reset();
    ASSERT_EQ(w_ptr.use_count(), 1);

    // 再释放一个 `shared_ptr`, 由于引用计数已经为 `0`, 故资源被释放
    s_ptr_2.reset();
    ASSERT_EQ(w_ptr.use_count(), 0);

    // 由于所有相关的 `shared_ptr` 实例都被释放, 故对应的 `weak_ptr` 实例变为无效
    ASSERT_TRUE(w_ptr.expired());

    // 通过无效 `weak_ptr` 实例获取的 `shared_ptr` 实例也为无效实例
    s_ptr_1 = w_ptr.lock();
    ASSERT_FALSE(s_ptr_1);
}
