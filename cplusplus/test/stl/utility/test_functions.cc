#include <gtest/gtest.h>

#include <utility>
#include <string>
#include <type_traits>

#include "reference/forward.h"

#include "stl/utility/functions.h"

#define TEST_SUITE_NAME test_cplusplus_stl_utility__functions

using namespace std;
using namespace cxx::stl;
using namespace cxx::reference;

/// https://learn.microsoft.com/zh-cn/cpp/standard-library/utility-functions?view=msvc-170

/// @brief 测试将可变引用转为只读引用的各类方法
TEST(TEST_SUITE_NAME, as_const) {
    int n = 100;

    // 无法编译通过, 因为传递的 `n` 为非 `const` 引用
    // only_const_reference(n);

    // 通过 `static_cast` 将 `n` 变量转为 `const` 引用, 可通过编译
    only_const_reference(static_cast<const int&>(n));

    // 通过 `const_cast` 将 `n` 变量转为 `const` 引用, 可通过编译
    only_const_reference(const_cast<const int&>(n));

    // 通过 `decltype` 获取 `n` 变量类型, 并通过 `static_cast` 转为 `const` 引用, 可通过编译
    only_const_reference(static_cast<const decltype(n)&>(n));

    // 通过 `remove_reference_t` 获取 `n` 变量的基本类型 (即如果 `n` 为引用类型, 则去掉引用)
    // 通过 `decltype` 获取 `n` 变量类型, 并通过 `add_const_t` 转为 `const` 引用, 可通过编译
    only_const_reference(static_cast<add_const_t<remove_reference_t<decltype(n)>>&>(n));

    // 通过 `std::as_const` 将 `n` 变量转为 `const` 引用, 可通过编译
#if __ge_cxx17
    only_const_reference(std::as_const<int>(n));
#else
    only_const_reference(const_cast<const int&>(n));
#endif
}

/// @brief `std::declval` 函数用于返回指定类型的一个 "右值引用", 该右值引用未引用到任何内容上, 仅可用于类型推断
///
/// `std::declval<T>()` ​在类型 `T` 没有定义默认构造函数或 `T` 为纯虚类类型时, 仍然能获取到该类型的右值引用,
/// 配合 `decltype` 和 `sizeof` 关键字, 即可推断出 `T` 的实际类型以及占用内存大小
///
/// 本例中的所有用法, 都可以在模板中替换为泛型参数 (例如 `T`)
TEST(TEST_SUITE_NAME, decltype) {
    // 通过产生一个 `int&&` 引用, 推断 `int` 类型的大小
    ASSERT_EQ(sizeof(std::declval<int>()), 4);

    // 通过产生一个 `int&&` 引用, 推断 `a` 变量的类型为 `int&&`
    decltype(std::declval<int>()) a = 2;
    ASSERT_TRUE((is_same<decltype(a), int&&>::value));

    // 通过 `string&& + const char*&&` 的计算结果类型, 推断 `b` 变量的类型为 `string`
    decltype(std::declval<string>() + std::declval<const char*>()) b = "Hello";
    ASSERT_TRUE((is_same<decltype(b), string>::value));

    // 通过 `(string&&).c_str()` 方法的调用结果类型, 推断 `c` 变量的类型为 `const char*`
    decltype(std::declval<string>().c_str()) c = "Hello";
    ASSERT_TRUE((is_same<decltype(c), const char*>::value));
}

/// @brief `std::exchange` 函数将指定变量值替换为新值, 并返回其原本的值
///
/// `std::exchange` 函数的两个参数可以为不同类型, 只要这两个类型允许赋值操作即可,
/// 例如 `double` 和 `int` 类型
TEST(TEST_SUITE_NAME, exchange) {
    // 将 `s1` 变量的值进行替换, 并将原本的值给 `s2` 变量
    string s1 = "Hello", s2;
    s2 = std::exchange(s1, "World");
    ASSERT_EQ(s2, "Hello");
    ASSERT_EQ(s1, "World");

    // 将 `n1` 变量的值进行替换, 并将原本的值给 `n2` 变量
    double n1 = 1.2, n2;
    n2 = std::exchange(n1, int(2));
    ASSERT_EQ(n1, 2.0);
    ASSERT_EQ(n2, 1.2);
}

/// @brief `std::forward` 函数的参数如果是右值 (或右值引用), 则返回该参数的右值引用,
/// 否则返回该参数本身
///
/// `std::forward` 主要用于模板函数内部, 对函数参数进行 "完美转发", 以根据函数参数传入的情况
/// (左值或右值), 调用不同的重载函数 (例如拷贝构造器或移动构造器)
TEST(TEST_SUITE_NAME, forward) {
    int a = 1;
    int& ra = a;

    // 参数为左值引用情况, 转发为左值引用
    ASSERT_EQ(do_forward(a), LEFT_REF);
    ASSERT_EQ(do_forward(ra), LEFT_REF);

    // 参数为右值引用情况, 转发为右值引用
    ASSERT_EQ(do_forward(1), RIGHT_REF);
    ASSERT_EQ(do_forward(std::move(a)), RIGHT_REF);
    ASSERT_EQ(do_forward([]() {return 100;}()), RIGHT_REF);
}

