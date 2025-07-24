#include <gtest/gtest.h>

#include <memory>

#include "large_object.h"

#define TEST_SUITE_NAME test_cplusplus_ptr__unique_ptr

using namespace std;
using namespace cxx::pointer;

/// @brief 测试创建 `unique_ptr` 智能指针
///
/// 可以通过 `unique_ptr` 类构造器或者 `make_unique` 函数来创建 `unique_ptr` 实例,
/// 推荐使用后者, 可以保证编译时的类型安全以及内存分配和回收的一致性
TEST(TEST_SUITE_NAME, make_unique_ptr) {
    // 通过 `unique_ptr` 类构造器创建实例
    unique_ptr<LargeObject<int, 10>> ptr = unique_ptr<LargeObject<int, 10>>(
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

    // 通过 `make_unique` 函数创建 `unique_ptr` 实例
    ptr = make_unique<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // `unique_ptr` 重载了 `operator bool()` 操作符, 可以作为 `bool` 类型使用;
    // `ptr` 变量为 `true` 表示 `unique_ptr` 对象有效
    ASSERT_TRUE(ptr);

    ASSERT_EQ(ptr->size(), 10);
    ASSERT_EQ((*ptr)[0], 1);
    // ...
    ASSERT_EQ((*ptr)[4], 5);
    ASSERT_EQ((*ptr)[ptr->size() - 1], 10);
}

/// @brief 测试 `unique_ptr` 智能指针的移动赋值
TEST(TEST_SUITE_NAME, move_unique_ptr) {
    unique_ptr<LargeObject<int, 10>> ptr1 = make_unique<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // `ptr1` 变量为 `true` 表示 `unique_ptr` 对象有效
    ASSERT_TRUE(ptr1);

    // `unique_ptr` 的拷贝构造器不可用
    // unique_ptr<LargeObject<int, 10>> ptr2 = ptr1;

    // `unique_ptr` 的赋值运算符不可用
    // unique_ptr<LargeObject<int, 10>> ptr2;
    // ptr2 = ptr1;

    // 如果一定要将一个 `unique_ptr` 变量赋值给另一个, 则必须使用移动语义 (`std::move`)
    // 调用移动构造器 `unique_ptr(unique_ptr&&)`
    unique_ptr<LargeObject<int, 10>> ptr2 = std::move(ptr1);

    // `ptr2` 变量为 `true`, `ptr1` 变量为 `false` 表示 `ptr1` 变量的内容已经移动到 `ptr2` 变量
    ASSERT_TRUE(ptr2);
    ASSERT_FALSE(ptr1);

    ASSERT_EQ(ptr2->size(), 10);
    ASSERT_EQ((*ptr2)[0], 1);
    // ...
    ASSERT_EQ((*ptr2)[4], 5);
    ASSERT_EQ((*ptr2)[ptr2->size() - 1], 10);

    // 调用移动赋值运算符 (`unique_ptr& operator=(unique_ptr&&)`) 将 `unique_ptr` 变量进行赋值;
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

/// @brief 测试 `unique_ptr` 对象中获取其保存的指针
TEST(TEST_SUITE_NAME, get_object_ptr_from_unique_ptr) {
    unique_ptr<LargeObject<int, 10>> ptr = make_unique<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // 通过 `unique_ptr::get` 方法获取实际对象的裸指针值,
    // 此时实际对象依旧被 `unique_ptr` 对象管理
    LargeObject<int, 10>* p_obj = ptr.get();

    // 获取指针后, 原本的 `unique_ptr` 对象依旧有效
    ASSERT_TRUE(ptr);

    ASSERT_EQ(p_obj->size(), 10);
    ASSERT_EQ((*p_obj)[0], 1);
    // ...
    ASSERT_EQ((*p_obj)[4], 5);
    ASSERT_EQ((*p_obj)[ptr->size() - 1], 10);
}

/// @brief 测试 `unique_ptr` 对象中获取其保存的指针
TEST(TEST_SUITE_NAME, release_object_from_unique_ptr_object) {
    unique_ptr<LargeObject<int, 10>> ptr = make_unique<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // 通过 `unique_ptr::release` 方法获取实际对象的裸指针值,
    // 此时实际对象不再被 `unique_ptr` 对象管理
    LargeObject<int, 10>* p_obj = ptr.release();

    // 获取指针后, 原本的 `unique_ptr` 对象不再有效
    ASSERT_FALSE(ptr);

    ASSERT_EQ(p_obj->size(), 10);
    ASSERT_EQ((*p_obj)[0], 1);
    // ...
    ASSERT_EQ((*p_obj)[4], 5);
    ASSERT_EQ((*p_obj)[ptr->size() - 1], 10);

    // 此时要通过 `unique_ptr` 的 `deleter` 手动释放对象裸指针
    ptr.get_deleter()(p_obj);
}

/// @brief 测试交换两个 `unique_ptr` 对象中托管的目标对象裸指针
TEST(TEST_SUITE_NAME, swap_object_ptr_in_two_unique_ptr_object) {
    unique_ptr<LargeObject<int, 10>>
        ptr1 = make_unique<LargeObject<int, 10>>(
            initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
        ),
        ptr2 = make_unique<LargeObject<int, 10>>(
            initializer_list<int>{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }
        );

    // 交换两个 `unique_ptr` 托管的对象指针
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

/// @brief 重新设置 `unique_ptr` 对象中托管的目标对象裸指针
///
/// 在调用 `unique_ptr::reset` 方法时, 如果之前已经有对象指针托管, 则会释放之前托管的对象
TEST(TEST_SUITE_NAME, reset_unique_ptr_object) {
    unique_ptr<LargeObject<int, 10>> ptr = make_unique<LargeObject<int, 10>>(
        initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // 将托管的指针重设为 `null` 值
    ptr.reset();
    ASSERT_FALSE(ptr);

    // 将托管的指针重设为另一个指针值
    ptr.reset(
        make_unique<LargeObject<int, 10>>(
            initializer_list<int>{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }
        )
        .release()
    );

    ASSERT_TRUE(ptr);

    ASSERT_EQ(ptr->size(), 10);

    ASSERT_EQ((*ptr)[0], 10);
    // ...
    ASSERT_EQ((*ptr)[4], 50);
    ASSERT_EQ((*ptr)[ptr->size() - 1], 100);
}

/// @brief 测试通过 `unique_ptr` 类创建指向数组资源的指针
///
/// 除非有特殊情况, 否则不应通过 `unique_ptr` 类来创建指向数组的指针,
/// 而应该通过 `vector` 容器类型来完成
TEST(TEST_SUITE_NAME, make_unique_ptr_object_for_array) {
    function<void(unique_ptr<LargeObject<int, 3>[]>&, size_t, size_t)> fn_fill
        = [](unique_ptr<LargeObject<int, 3>[]>& ptr, size_t size, size_t n)
    {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < n; ++j) {
                ptr[i][j] = i * 10 + j;
            }
        }
    };

    // 通过 `unique_ptr` 类构造器创建
    unique_ptr<LargeObject<int, 3>[]> ptr = unique_ptr<LargeObject<int, 3>[]>(new LargeObject<int, 3>[5]);
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

    // 通过 `shared_ptr` 类构造器创建
    ptr = make_unique<LargeObject<int, 3>[]>(5);
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
}
