#if __ge_cxx17

#include <gtest/gtest.h>

#include "oop/unpack.h"

#define TEST_SUITE_NAME test_cplusplus_oop__unpack

using namespace cxx::oop;

/// @brief C++ 17 后的版本, 可以将结构体 (或类对象) 的字段值按照字段顺序展开到各个变量中,
/// 也可以将数组的元素值按顺序展开到各个变量中;
///
/// 在结构体 (或数组) 展开到变量时, 变量的数量必须和结构体字段数量 (或数组元素数量) 相同
TEST(TEST_SUITE_NAME, unpack_object) {
    // 定义一个具备三个字段的结构体实例
    Unpack obj = Unpack{ 1, 2, 3, { -1, -2, -3 } };

    // 将结构体实例的字段按顺序展开到 4 个变量中
    auto [x, y, z, data] = obj;

    // 将数组元素展开到变量
    auto [a, b, c] = data;

    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);
    ASSERT_EQ(z, 3);
    ASSERT_EQ(a, -1);
    ASSERT_EQ(b, -2);
    ASSERT_EQ(c, -3);

    // 将实例字段的引用按顺序展开到 3 个变量中
    auto& [rx, ry, rz, rdata] = obj;

    // 将数组元素的引用展开到变量
    auto& [ra, rb, rc] = rdata;

    rx = 100;
    ry = 200;
    rz = 300;
    ra = -100;
    rb = -200;
    rc = -300;

    ASSERT_EQ(obj.x, 100);
    ASSERT_EQ(obj.y, 200);
    ASSERT_EQ(obj.z, 300);
    ASSERT_EQ(obj.data[0], -100);
    ASSERT_EQ(obj.data[1], -200);
    ASSERT_EQ(obj.data[2], -300);
}

#endif // __ge_cxx17