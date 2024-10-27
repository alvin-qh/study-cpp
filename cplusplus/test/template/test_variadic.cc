#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "template/variadic.h"

#include <string>
#include <vector>

#define TEST_SUITE_NAME test_cplusplus_template__variadic

using namespace std;
using namespace cxx::templated;

using testing::ElementsAre;

/// @brief 测试不定模板参数的类
///
/// 通过不定模板参数向该类型传递构造器参数
class TestClass {
private:
    double _x, _y, _z;
public:
    TestClass() : TestClass(0) {}
    TestClass(double val) : TestClass(val, val, val) {}
    TestClass(double x, double y, double z) : _x(x), _y(y), _z(z) {}
    TestClass(const TestClass&) = default;
    virtual ~TestClass() = default;

    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }
};

/// @brief 测试通过不定模板参数调用不同重载的构造器
TEST(TEST_SUITE_NAME, variadic_template_arguments) {
    TestClass o = create_object<TestClass>();
    ASSERT_EQ(o.x(), 0);
    ASSERT_EQ(o.y(), 0);
    ASSERT_EQ(o.z(), 0);

    o = create_object<TestClass>(0.1);
    ASSERT_EQ(o.x(), 0.1);
    ASSERT_EQ(o.y(), 0.1);
    ASSERT_EQ(o.z(), 0.1);

    o = create_object<TestClass>(0.1, 0.2, 0.3);
    ASSERT_EQ(o.x(), 0.1);
    ASSERT_EQ(o.y(), 0.2);
    ASSERT_EQ(o.z(), 0.3);
}

/// @brief 定义函数, 测试可变模板参数函数 (两个参数)
/// @param a 参数 1
/// @param b 参数 2
/// @return 返回值
int _add(int a, int b) { return a + b; }

/// @brief 定义仿函数, 测试可变参数模板函数 (三个参数)
///
/// @tparam T 参数类型
template<typename T>
struct Collect {
    /// @brief 重载 `()` 运算符, 定义仿函数
    /// @param a 参数 1
    /// @param b 参数 2
    /// @param c 参数 3
    /// @return 返回值
    vector<T> operator()(T a, T b, T c) const {
        vector<T> v;
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);

        return v;
    }
};

/// @brief 测试可变模板参数展开为函数参数列表
TEST(TEST_SUITE_NAME, callback) {
    // 将两个模板参数展开为 `_add` 函数的参数列表
    int r1 = callback<int>(_add, 1, 2);
    ASSERT_EQ(r1, 3);

    // 将三个模板参数展开为 lambda 函数的参数列表
    double r2 = callback<double>(
        [](double a, int b, double c) { return a + b + c; },
        1.1,
        2,
        3.3
    );
    ASSERT_EQ(r2, 6.4);

    Collect<string> coll;
    // 将三个模板参数展开为 "仿函数" 的参数列表
    vector<string> r3 = callback<vector<string>>(coll, string("A"), string("B"), string("C"));
    ASSERT_EQ(r3.size(), 3);
    ASSERT_THAT(r3, ElementsAre(string("A"), string("B"), string("C")));
}

/// @brief 测试通过递归方式调用可变模板参数函数
TEST(TEST_SUITE_NAME, recursive_args) {
    // 通过对可变模板参数的递归访问参数列表
    int r1 = recursive_args(1, 2, 3, 4, 5);
    ASSERT_EQ(r1, 15);

    // 通过对可变模板参数的递归访问参数列表
    string r2 = recursive_args(string("A"), "B", "C", "D");
    ASSERT_EQ(r2, "ABCD");
}
