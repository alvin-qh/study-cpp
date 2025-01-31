#include <gtest/gtest.h>

#include <memory>

#include "large_object.h"

#define TEST_SUITE_NAME test_cplusplus_ptr__shared_ptr

using namespace std;
using namespace cxx::pointer;

/// @brief 测试创建 `shared_ptr` 智能指针
///
/// 可以通过 `shared_ptr` 类构造器或者 `make_shared` 函数来创建 `shared_ptr` 实例,
/// 推荐使用后者, 可以保证编译时的类型安全以及内存分配和回收的一致性
TEST(TEST_SUITE_NAME, make_shared_ptr) {
    // 通过 `shared_ptr` 类构造器创建实例
    shared_ptr<LargeObject<int, 10>> ptr = shared_ptr<LargeObject<int, 10>>(
        new LargeObject<int, 10>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );
    // `shared_ptr` 重载了 `operator bool()` 操作符, 可以作为 `bool` 类型使用;
    // `ptr` 变量为 `true` 表示 `shared_ptr` 对象有效
    ASSERT_TRUE(ptr);

    ASSERT_EQ(ptr->size(), 10);
    ASSERT_EQ((*ptr)[0], 1);
    // ...
    ASSERT_EQ((*ptr)[4], 5);
    ASSERT_EQ((*ptr)[ptr->size() - 1], 10);

    // 通过 `make_shared` 函数创建实例
    ptr = make_shared<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    ASSERT_TRUE(ptr);

    ASSERT_EQ(ptr->size(), 10);
    ASSERT_EQ((*ptr)[0], 1);
    // ...
    ASSERT_EQ((*ptr)[4], 5);
    ASSERT_EQ((*ptr)[ptr->size() - 1], 10);
}

/// @brief 测试 `shared_ptr` 智能指针的赋值
TEST(TEST_SUITE_NAME, assign_shared_ptr) {
    shared_ptr<LargeObject<int, 10>> ptr1 = make_shared<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // `ptr1` 变量为 `true` 表示 `unique_ptr` 对象有效
    ASSERT_TRUE(ptr1);

    // 确认当前对象的引用计数器为 `1`
    ASSERT_EQ(ptr1.use_count(), 1);

    // 调用拷贝构造器 `shared_ptr(shared_ptr&)`, 通过增加引用计数, 令两个变量都引用到同一个资源
    shared_ptr<LargeObject<int, 10>> ptr2 = ptr1;

    // `ptr1` 和 `ptr2` 变量为 `true`, 表示均为有效对象
    ASSERT_TRUE(ptr1);
    ASSERT_TRUE(ptr2);

    // 确认 `shared_ptr` 对象的引用计数器增加
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);

    ASSERT_EQ(ptr1->size(), 10);
    ASSERT_EQ(ptr2->size(), 10);
    ASSERT_EQ((*ptr1)[0], 1);
    ASSERT_EQ((*ptr2)[0], 1);
    // ...
    ASSERT_EQ((*ptr1)[4], 5);
    ASSERT_EQ((*ptr2)[4], 5);
    ASSERT_EQ((*ptr1)[ptr2->size() - 1], 10);
    ASSERT_EQ((*ptr2)[ptr2->size() - 1], 10);

    // 释放其中一个对象引用的资源, 减少引用计数
    ptr1.reset();
    ASSERT_FALSE(ptr1);
    ASSERT_EQ(ptr2.use_count(), 1);

    // 调用赋值运算符 (`unique_ptr& operator=(unique_ptr&)`) 将 `shared_ptr` 变量进行赋值;
    ptr1 = ptr2;
    ASSERT_TRUE(ptr1);
    ASSERT_TRUE(ptr2);

    // 确认 `shared_ptr` 对象的引用计数器增加
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);

    ASSERT_EQ(ptr1->size(), 10);
    ASSERT_EQ(ptr2->size(), 10);
    ASSERT_EQ((*ptr1)[0], 1);
    ASSERT_EQ((*ptr2)[0], 1);
    // ...
    ASSERT_EQ((*ptr1)[4], 5);
    ASSERT_EQ((*ptr2)[4], 5);
    ASSERT_EQ((*ptr1)[ptr2->size() - 1], 10);
    ASSERT_EQ((*ptr2)[ptr2->size() - 1], 10);
}

/// @brief 测试 `shared_ptr` 智能指针的移动赋值
TEST(TEST_SUITE_NAME, move_shared_ptr) {
    shared_ptr<LargeObject<int, 10>> ptr1 = make_shared<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // `ptr1` 变量为 `true` 表示 `unique_ptr` 对象有效
    ASSERT_TRUE(ptr1);

    // 通过移动语义 `std::move` 调用移动构造器 `shared_ptr(shared_ptr&&)`, 可以将 `shared_ptr`
    // 内部资源进行移动
    shared_ptr<LargeObject<int, 10>> ptr2 = std::move(ptr1);

    // `ptr2` 变量为 `true`, `ptr1` 变量为 `false` 表示 `ptr1` 变量的内容已经移动到 `ptr2` 变量
    ASSERT_TRUE(ptr2);
    ASSERT_FALSE(ptr1);

    ASSERT_EQ(ptr2->size(), 10);
    ASSERT_EQ((*ptr2)[0], 1);
    // ...
    ASSERT_EQ((*ptr2)[4], 5);
    ASSERT_EQ((*ptr2)[ptr2->size() - 1], 10);

    // 调用移动赋值运算符 (`unique_ptr& operator=(unique_ptr&&)`) 将 `shared_ptr` 变量进行赋值;
    // `ptr2` 变量为 `true`, `ptr1` 变量为 `false` 表示 `ptr1` 变量的内容已经移动到 `ptr2` 变量
    ptr1 = std::move(ptr2);
    ASSERT_TRUE(ptr1);
    ASSERT_FALSE(ptr2);

    ASSERT_EQ(ptr1->size(), 10);
    ASSERT_EQ((*ptr1)[0], 1);
    // ...
    ASSERT_EQ((*ptr1)[4], 5);
    ASSERT_EQ((*ptr1)[ptr1->size() - 1], 10);
}

/// @brief 测试 `shared_ptr` 对象中获取其保存的指针
TEST(TEST_SUITE_NAME, get_object_ptr_from_shared_ptr) {
    shared_ptr<LargeObject<int, 10>> ptr = make_shared<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // 通过 `shared_ptr::get` 方法获取实际对象的裸指针值,
    // 此时实际对象依旧被 `shared_ptr` 对象管理
    LargeObject<int, 10>* p_obj = ptr.get();

    // 获取指针后, 原本的 `shared_ptr` 对象依旧有效
    ASSERT_TRUE(ptr);

    ASSERT_EQ(p_obj->size(), 10);
    ASSERT_EQ((*p_obj)[0], 1);
    // ...
    ASSERT_EQ((*p_obj)[4], 5);
    ASSERT_EQ((*p_obj)[ptr->size() - 1], 10);
}

/// @brief 测试交换两个 `shared_ptr` 对象中托管的目标对象裸指针
TEST(TEST_SUITE_NAME, swap_object_ptr_in_two_shared_ptr_object) {
    shared_ptr<LargeObject<int, 10>>
        ptr1 = make_shared<LargeObject<int, 10>>(
            initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
        ),
        ptr2 = make_shared<LargeObject<int, 10>>(
            initializer_list<int>{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }
        );

    // 交换两个 `shared_ptr` 托管的对象指针
    ptr1.swap(ptr2);

    ASSERT_TRUE(ptr1);
    ASSERT_TRUE(ptr2);

    ASSERT_EQ(ptr1->size(), 10);
    ASSERT_EQ(ptr2->size(), 10);

    ASSERT_EQ((*ptr2)[0], 1);
    // ...
    ASSERT_EQ((*ptr2)[4], 5);
    ASSERT_EQ((*ptr2)[ptr2->size() - 1], 10);

    ASSERT_EQ((*ptr1)[0], 10);
    // ...
    ASSERT_EQ((*ptr1)[4], 50);
    ASSERT_EQ((*ptr1)[ptr1->size() - 1], 100);
}

/// @brief 重新设置 `shared_ptr` 对象中托管的目标对象裸指针
///
/// 在调用 `shared_ptr::reset` 方法时, 如果之前已经有对象指针托管, 则会释放之前托管的对象
TEST(TEST_SUITE_NAME, reset_unique_ptr_object) {
    shared_ptr<LargeObject<int, 10>> ptr = make_shared<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // 将托管的指针重设为 `null` 值
    ptr.reset();
    ASSERT_FALSE(ptr);

    // 将托管的指针重设为另一个指针值
    ptr.reset(
        make_unique<LargeObject<int, 10>>(
            initializer_list<int>{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }
        ).release()
    );

    ASSERT_TRUE(ptr);

    ASSERT_EQ(ptr->size(), 10);

    ASSERT_EQ((*ptr)[0], 10);
    // ...
    ASSERT_EQ((*ptr)[4], 50);
    ASSERT_EQ((*ptr)[ptr->size() - 1], 100);

    ptr.reset(
        new LargeObject<int, 10>(
            initializer_list<int>{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }
        ),
        [](LargeObject<int, 10>* p) { delete p; }
    );
}

/// @brief 测试通过 `shared_ptr` 类创建指向数组资源的指针
///
/// 除非有特殊情况, 否则不应通过 `shared_ptr` 类来创建指向数组的指针,
/// 而应该通过 `vector` 容器类型来完成
TEST(TEST_SUITE_NAME, make_shared_ptr_object_for_array) {
    function<void(shared_ptr<LargeObject<int, 3>[]>&, size_t, size_t)> fn_fill
        = [](shared_ptr<LargeObject<int, 3>[]>& ptr, size_t size, size_t n)
    {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < n; ++j) {
                ptr[i][j] = i * 10 + j;
            }
        }
    };

    // 通过 `shared_ptr` 类构造器创建
    shared_ptr<LargeObject<int, 3>[]> ptr = shared_ptr<LargeObject<int, 3>[]>(new LargeObject<int, 3>[5]);
    fn_fill(ptr, 5, 3);

    ASSERT_EQ(ptr[0][0], 0);
    ASSERT_EQ(ptr[0][1], 1);
    ASSERT_EQ(ptr[0][2], 2);
    ASSERT_EQ(ptr[1][0], 10);
    ASSERT_EQ(ptr[1][1], 11);
    ASSERT_EQ(ptr[1][2], 12);
    // ...
    ASSERT_EQ(ptr[4][0], 40);
    ASSERT_EQ(ptr[4][1], 41);
    ASSERT_EQ(ptr[4][2], 42);

#if __ge_cxx20
    // 通过 `shared_ptr` 类构造器创建数组, 参数为数组长度, C++ 20 以上版本有效
    ptr = make_shared<LargeObject<int, 3>[]>(5);
    fn_fill(ptr, 5, 3);

    ASSERT_EQ(ptr[0][0], 0);
    ASSERT_EQ(ptr[0][1], 1);
    ASSERT_EQ(ptr[0][2], 2);
    ASSERT_EQ(ptr[1][0], 10);
    ASSERT_EQ(ptr[1][1], 11);
    ASSERT_EQ(ptr[1][2], 12);
    // ...
    ASSERT_EQ(ptr[4][0], 40);
    ASSERT_EQ(ptr[4][1], 41);
    ASSERT_EQ(ptr[4][2], 42);
#endif
}
