#include <gtest/gtest.h>

#include <string>

#include "reference/right_ref.h"

#define TEST_SUITE_NAME test_cplusplus_reference__right_ref

using namespace std;
using namespace cxx::reference;


/// @brief 测试右值引用
///
/// 所谓右值, 即只能出现在赋值运算符 "右边" 的值, 这类值均为 "临时" 值, 包括:
///
/// - 值类型函数返回值;
/// - 临时对象;
/// - 值传递的函数参数;
///
/// 这些 "临时值" 在通过赋值传递时, 会通过 C++ 的拷贝构造器或赋值操作,
/// 往往会导致源对象的销毁和新对象的产生, 带来性能损耗
///
/// 通过 `&&` 运算符, C++ 允许为右值建立引用, 称为 "右值引用",
/// 右值引用可以临时获取到右值的所有权, 通过这种方式, 即可避免额外的构造和析构动作
TEST(TEST_SUITE_NAME, check_if_right_reference) {
    // 临时变量/对象为右值引用
    ASSERT_TRUE(is_right_reference<int>::test(int(0)));
    ASSERT_TRUE(is_right_reference<int>::test(100));
    ASSERT_TRUE(is_right_reference<string>::test("Hello"));
    ASSERT_TRUE(is_right_reference<string>::test(string("Hello")));

    // 具有返回值的函数调用表现为一个右值
    ASSERT_TRUE(is_right_reference<string>::test([] { return string("Hello"); } ()));

    // 引用类型变量为一个左值
    int n = 100;
    int& rn = n;
    ASSERT_FALSE(is_right_reference<int>::test(rn));

    // 右值引用变量本身也是一个左值
    int&& rrn = 100;
    ASSERT_FALSE(is_right_reference<int>::test(rrn));
}

/// @brief 获取左值临时的右值引用
///
/// 一些时候, 需要获取一个左值的临时 "右值引用";
/// 获取右值引用的目的是得到一个区别于 “左值引用” 的引用类型,
/// 在为发生 “移动语义” 的情况下提供类型支持
TEST(TEST_SUITE_NAME, left_to_right_reference) {
    int n1 = 100;

    ASSERT_FALSE(is_right_reference<int>::test(n1));

    // 通过 `static_cast` 操作符即可将左值引用转为右值引用
    ASSERT_TRUE(is_right_reference<int>::test(static_cast<int&&>(n1)));
}
