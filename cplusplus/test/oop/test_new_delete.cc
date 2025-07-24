#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsizeof-array-div"

#include <gtest/gtest.h>

#include <cstddef>

#include "oop/new_delete.h"

#define TEST_SUITE_NAME test_cplusplus_oop__new_delete

using namespace cxx::oop;

/// @brief 测试通过 `operator new(size_t)` 操作分配内存,
/// 并通过 `operator delete(void*)` 操作进行回收
TEST(TEST_SUITE_NAME, global_new_delete_operator) {
    int* p = new int(100);
    ASSERT_EQ(*p, 100);

    delete p;
}

/// @brief 测试通过 `operator new(size_t, const std::nothrow_t&)` 操作分配内存,
/// 并通过 `operator delete(void*, const std::nothrow_t&)` 操作进行回收
TEST(TEST_SUITE_NAME, global_nothrow_new_delete_operator) {
    int* p = new (std::nothrow) int(100);
    ASSERT_EQ(*p, 100);

    ::operator delete(p, std::nothrow);
}

/// @brief 测试通过 `operator new[](size_t)` 操作分配内存,
/// 并通过 `operator delete[](void*)` 操作进行回收
TEST(TEST_SUITE_NAME, global_array_new_delete_operator) {
    int* ps =
#if __ge_cxx17
        new int[] {1, 2, 3, 4};
#else
        new int[4] {1, 2, 3, 4};
#endif

    ASSERT_EQ(ps[0], 1);
    ASSERT_EQ(ps[1], 2);
    ASSERT_EQ(ps[2], 3);
    ASSERT_EQ(ps[3], 4);

    delete[] ps;
}

/// @brief 测试通过 `operator new[](size_t, std::nothrow_t)` 操作分配内存,
/// 并通过 `operator delete[](void*, const std::nothrow_t)` 操作进行回收
TEST(TEST_SUITE_NAME, global_nothrow_array_new_delete_operator) {
    int* ps =
#if __ge_cxx17
        new (std::nothrow) int[] {1, 2, 3, 4};
#else
        new (std::nothrow) int[4] {1, 2, 3, 4};
#endif

    ASSERT_EQ(ps[0], 1);
    ASSERT_EQ(ps[1], 2);
    ASSERT_EQ(ps[2], 3);
    ASSERT_EQ(ps[3], 4);

    ::operator delete[](ps, std::nothrow);
}

/// @brief 定义测试类, 用于测试
class A {
public:
    A(int val) : _val(val) { }
    virtual ~A() { }
    int value() { return _val; }
    int value() const { return _val; }

private:
    int _val;
};

/// @brief 测试 `placement new` 运算符
///
/// 所谓 `placement new` 操作符, 即在当前一块现有内存区域上, 执行指定类型的构造函数,
/// 将这块内存实例化成所需对象
///
/// 使用 `placement new` 操作符, 需要: 1. 手动分配内存; 2. 手动执行对象的析构函数;
/// 3. 手动释放内存;
TEST(TEST_SUITE_NAME, placement_new) {
#if __ge_cxx17
    std::byte buf[sizeof(A) * 10];
#else
    uint8_t buf[sizeof(A) * 10];
#endif
    A* pa = reinterpret_cast<A*>(buf);

    for (std::size_t i = 0; i < sizeof(buf) / sizeof(A); ++i) {
        // 通过 `placement new` 操作符调用构造器
        new (pa + i) A(i + 1);
    }

    ASSERT_EQ(pa[0].value(), 1);
    ASSERT_EQ(pa[5].value(), 6);
    ASSERT_EQ(pa[9].value(), 10);

    for (std::size_t i = 0; i < sizeof(buf) / sizeof(A); ++i) {
        // 调用析构函数
        pa[i].~A();
    }
}

/// @brief 测试通过类中定义的 `new/delete` 操作符分配内存
TEST(TEST_SUITE_NAME, class_override_new_delete_operator) {
    NewDelete* po = new NewDelete("object-1");
    ASSERT_EQ(po->name(), "object-1");

    delete po;

    NewDelete* pos =
#if __ge_cxx17
        new NewDelete[]{ NewDelete("object-1"), NewDelete("object-2") };
#else
        new NewDelete[2]{ NewDelete("object-1"), NewDelete("object-2") };
#endif

    ASSERT_EQ(pos[0].name(), "object-1");
    ASSERT_EQ(pos[1].name(), "object-2");

    delete[] pos;
}

#pragma clang diagnostic pop
