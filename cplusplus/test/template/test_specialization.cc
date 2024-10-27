#include <gtest/gtest.h>

#include "template/specialization.h"

#define TEST_SUITE_NAME test_cplusplus_template__specialization

using namespace std;
using namespace cxx::templated;

/// @brief 测试类型特化
TEST(TEST_SUITE_NAME, class_specialization) {
    // 测试 `template<typename T1, typename T2> class Special` 原始模板
    Special<char, int> s1('A', 1001);
    ASSERT_EQ(s1.to_string(), "Special<T1, T2>(A, 1001)");

    // 测试 `template<typename T> class Special<T, string>` 特化模板
    Special<int, string> s2(1, "Hello");
    ASSERT_EQ(s2.to_string(), "Special<T, string>(1, Hello)");

    // 测试 `template<typename T> class Special<T, T>` 特化模板
    Special<int, int> s3(100, 200);
    ASSERT_EQ(s3.to_string(), "Special<T, T>(100, 200)");
    ASSERT_TRUE(s3.same_generic_args());

    // 测试 `template<> class Special<string, string>` 特化模板
    Special<string, string> s4("Hello", "World");
    ASSERT_EQ(s4.to_string(), "Special<string, string>(Hello, World)");
    ASSERT_EQ(s4.concat(" "), "Hello World");

    int n = 1;
    double d = 1.1;

    // 测试 `template<typename T1, typename T2> class Special<T1*, T2*>` 特化模板
    Special<int*, double*> s5(&n, &d);
    ASSERT_EQ(s5.to_string(), "Special<T1*, T2*>(1, 1.1)");
}
