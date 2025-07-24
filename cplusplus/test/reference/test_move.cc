#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <list>

#include "reference/move.h"

#define TEST_SUITE_NAME test_cplusplus_reference__move

using namespace std;
using namespace cxx::reference;

/// @brief 测试右值引用传递
TEST(TEST_SUITE_NAME, move_reference) {
    // 定义函数, 参数为一个左值引用
    function<void(int&)> l_func = [](int&) { };

    // 定义函数, 参数为一个右值引用
    function<void(int&&)> r_func = [](int&&) { };

    // 定义变量以及变量的引用以及右值引用变量
    int n = 1;
    int& rn = n;
    int&& rrn = std::move(n); // 将左值引用转为右值引用

    // 右值引用变量本身是左值, 故可以传递给 `int&` 类型参数
    l_func(rrn);

    // 右值引用变量本身是左值, 故无法传递给 `int&&` 类型参数
    // r_func(rrn);

    // 可以通过 `move` 将变量转为右值引用
    r_func(std::move(n));

    // 可以通过 `move` 将变量的引用转为右值引用
    r_func(std::move(rn));

    // 可以通过 `move` 将变量的右值引用变量转为右值引用
    r_func(std::move(rrn));
}

/// @brief 移动语义
///
/// 有了右值引用, 即可完成所谓的 "移动" 语义, 即将源对象的内容 "移动到" 目标对象.
///
/// C++ 中的 "移动语义" 必须通过右值来完成, 而 `std::move` 函数可以将一个 "左值"
/// (例如一个变量) 临时转为 "右值引用", 从而完成 "移动语义"
TEST(TEST_SUITE_NAME, std_move_string) {
    // 定义一个变量 (左值)
    string str1 = "Hello";

    // 通过 `std::move` 将左值转为右值引用, 通过 `std::string` 类型的 "移动构造器"
    // 将 `str1` 对象的内容移动到 `str2` 对象中
    string str2 = std::move(str1);

    // 确认内容已经移动到目标对象
    ASSERT_EQ(str2, "Hello");

    // 确认源对象的内容已经失效
    ASSERT_EQ(str1, "");

    vector<int> v1;
    for (int i = 0; i < 10; i++) {
        v1.push_back(i);
    }
    vector<int> v2 = std::move(v1);
    ASSERT_EQ(v1.size(), 0);
    ASSERT_EQ(v2.size(), 10);
}

/// @brief 移动语义
///
/// 有了右值引用, 即可完成所谓的 "移动" 语义, 即将源对象的内容 "移动到" 目标对象.
///
/// C++ 中的 "移动语义" 必须通过右值来完成, 而 `std::move` 函数可以将一个 "左值"
/// (例如一个变量) 临时转为 "右值引用", 从而完成 "移动语义"
TEST(TEST_SUITE_NAME, std_move_vector) {
    // 定义一个变量 (左值)
    vector<int> v1(10);

    // 通过 `std::move` 将左值转为右值引用, 通过 `std::vector` 类型的 "移动构造器"
    // 将 `v1` 对象的内容移动到 `v2` 对象中
    vector<int> v2 = std::move(v1);

    // 确认内容已经移动到目标对象
    ASSERT_EQ(v2.size(), 10);

    // 确认源对象的内容已经失效
    ASSERT_EQ(v1.size(), 0);
}

/// @brief 移动语义
///
/// 有了右值引用, 即可完成所谓的 "移动" 语义, 即将源对象的内容 "移动到" 目标对象.
///
/// C++ 中的 "移动语义" 必须通过右值来完成, 而 `std::move` 函数可以将一个 "左值"
/// (例如一个变量) 临时转为 "右值引用", 从而完成 "移动语义"
TEST(TEST_SUITE_NAME, std_move_list) {
    // 定义一个变量 (左值)
    list<int> l1;
    for (int i = 0; i < 10; i++) {
        l1.push_back(i);
    }

    // 通过 `std::move` 将左值转为右值引用, 通过 `std::list` 类型的 "移动构造器"
    // 将 `l1` 对象的内容移动到 `l2` 对象中
    list<int> l2 = std::move(l1);

    // 确认内容已经移动到目标对象
    ASSERT_EQ(l2.size(), 10);

    // 确认源对象的内容已经失效
    ASSERT_EQ(l1.size(), 0);
}

/// @brief 测试自定义类型的 "移动语义"
TEST(TEST_SUITE_NAME, moveable_class) {
    // 定义一个变量 (左值), 此时对象有效, 且内容正常
    Moveable<int> m1(100);
    ASSERT_TRUE(m1);
    ASSERT_EQ(*m1, 100);

    // 将 `m1` 变量转为右值引用, 并调用 `Moveable` 类型的 "移动构造器" 对对象进行移动
    // 完成移动后, `m1` 对象失效, 内容被移动到 `m2` 对象中
    Moveable<int> m2 = std::move(m1);
    ASSERT_EQ(*m2, 100);
    ASSERT_FALSE(m1);

    // 这里调用 `移动赋值运算符` 将 `m2` 变量内容移动到 `m1` 变量
    // 完成移动操作后, `m2` 对象失效, 内容被移动到 `m1` 对象中
    m1 = std::move(m2);
    ASSERT_TRUE(m1);
    ASSERT_EQ(*m1, 100);
    ASSERT_FALSE(m2);

    // 传参时, 如果实参是 "临时对象", 则可作为 "右值引用" 进行传参,
    // 这里的返回值也是一个 "临时对象" (刻意为之), 故返回值也可看作为一个 "右值引用"
    // 这里调用 "移动构造器" 创建 `m3` 对象
    Moveable<int> m3 = [](Moveable<int>&& m) { return Moveable<int>(*m); }(Moveable<int>(100));
    ASSERT_TRUE(m3);
    ASSERT_EQ(*m3, 100);

    // 这里调用 `移动赋值运算符` 将函数返回值内容移动到 `m3` 变量
    m3 = [](Moveable<int>&& m) { return Moveable<int>(*m); }(Moveable<int>(100));
    ASSERT_TRUE(m3);
    ASSERT_EQ(*m3, 100);

    // 这里 `m1` 是一个左值, 故无法作为 "右值引用" 进行传参
    // m3 = [](Moveable<int>&& m) { return m; }(m1);

    // 需要将 `m1` 转为 "右值引用" 后, 即可进行传参
    // 完成移动操作后, `m1` 对象失效, 内容被移动到 `m3` 对象中
    m3 =
#if __ge_cxx20
        [](Moveable<int>&& m) { return m; }(std::move(m1));
#else // 低于 C++ 20 版本, 返回值需要通过 `std::forward` 函数进行一次转发, 方能返回右值
        [](Moveable<int>&& m) { return std::forward<Moveable<int>>(m); }(std::move(m1));
#endif
    ASSERT_TRUE(m3);
    ASSERT_EQ(*m3, 100);
    ASSERT_FALSE(m1);
}
