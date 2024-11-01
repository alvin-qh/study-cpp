#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop__const

#include <string>

using namespace std;

/// @brief 测试 `const` 修饰值变量
///
/// 当使用 `const` 修饰值变量时, 表示该变量为只读变量, 不可以修改变量值
TEST(TEST_SUITE_NAME, const_value) {
    const int a = 100;
    ASSERT_EQ(a, 100);

    // 无法修改 const 变量
    // a = 1000;
}

/// @brief 测试 `const` 修饰引用变量
///
/// 当使用 `const` 修饰引用变量时, 表示该引用为只读引用,
/// 即不能通过该引用变量修改其引用变量的值
///
/// 对于类型 `T`, 可以有两种等效写法表示其只读引用: `const T&` 以及 `T const&`,
/// 表达相同含义
TEST(TEST_SUITE_NAME, const_reference) {
    int a = 100;

    // 定义到只读变量的引用
    const int& r1 = a;
    ASSERT_EQ(r1, 100);

    // 无法通过 const 引用修改变量
    // ra1 = 1000;

    // 定义到只读变量的引用, 与上面写法作用一致
    int const& r2 = a;
    ASSERT_EQ(r2, 100);

    // 无法通过 const 引用修改变量
    // ra2 = 1000;

    // 定义到只读变量的引用, 与上面写法作用一致,
    // 这种声明方法相当于重复了一个无效 `const` 关键字
    // const int const& r3 = a;

    // 无法通过 const 引用修改变量
    // ra3 = 1000;
}

/// @brief 测试 `const` 修饰指针变量
///
/// 当使用 `const` 修饰指针变量, 则根据 `const` 的位置不同, 对于类型 `T`, 其含义包括:
/// - 当 `const` 在 `*` 前 (包括 `const T*` 以及 `T const*`), 表示指针指向的值为只读;
/// - 当 `const` 在 `*` 后 (即 `T* const`), 表示指针变量本身为只读 (即指针不能改变);
/// - 结合上两条 (即 `const T* const`), 表示指针变量本身即其指向的值均为只读;
TEST(TEST_SUITE_NAME, const_pointer) {
    int a = 100, b = 200;

    // 1. 定义指向只读变量的指针, 即无法改变指针指向的值

    const int* p1 = &a;
    ASSERT_EQ(*p1, 100);

    // 无法改变指针指向的变量值
    // *pa1 = 1000;

    // 修改指针值, 指向新的变量
    p1 = &b;
    ASSERT_EQ(*p1, 200);

    // 2. 定义指向只读变量的指针, 相当于 1 的另一种写法

    int const* p2 = &a;
    ASSERT_EQ(*p2, 100);

    // 无法改变指针指向的变量值
    // *pa2 = 1000;

    // 修改指针值, 指向新的变量
    p2 = &b;
    ASSERT_EQ(*p2, 200);

    // 3. 定义只读指针, 即无法改变指针变量本身

    int* const p3 = &a;
    ASSERT_EQ(*p3, 100);

    // 修改指针指向的变量值
    *p3 = 1000;
    ASSERT_EQ(a, 1000);

    // 无法改变变量保存的指针
    // p3 = &b;

    // 4. 定义指向只读变量的只读指针, 即无法改变指针变量本身,
    // 也无法改变指针指向的变量值

    const int* const p4 = &a;
    ASSERT_EQ(*p4, 1000);

    // 无法改变变量保存的指针
    // p4 = &b;

    // 无法改变指针指向的变量值
    // *p4 = 10000;
}

/// @brief 测试类成员方法的 `const` 修饰符
///
/// 当使用 `const` 修饰类成员方法时, 其表示的是当前对象的状态, 包括:
/// - 无 `const` 修饰或修饰为 `&` 时, 表示该方法可用于可读写对象 (及引用), 无法用于只读对象 (及引用);
/// - 修饰为 `const` 或修饰为 `const&` 时, 表示该方法可用于可读写对象 (及引用) 以及只读对象 (及引用);
class Constant {
private:
    string _val, _ref, _ptr;
public:
    Constant(const string& val) :
        _val(val),
        _ref(val + "-r"),
        _ptr(val + "-p") {
    }

    /// @brief 将当前对象转为字符串
    ///
    /// 方法修饰为 
    ///
    /// @return 字符串 
    string to_string() const { return "Constant(" + _val + ")"; }

    string value() { return _val; }
    const string value() const { return _val; }

    string* ptr() { return &_ptr; }
    const string* ptr() const { return &_ptr; }

    string& ref()& { return _ref; }
    const string& ref() const& { return _ref; }
};


TEST(TEST_SUITE_NAME, const_with_method_for_non_const_object) {
    Constant c = Constant("TEST");
    ASSERT_EQ(c.to_string(), "Constant(TEST)");

    ASSERT_EQ(c.value(), "TEST");

    c.value() += "-new";
    ASSERT_EQ(c.value(), "TEST");

    ASSERT_EQ(c.ref(), "TEST-r");

    c.ref() += "-new";
    ASSERT_EQ(c.ref(), "TEST-r-new");

    ASSERT_EQ(*c.ptr(), "TEST-p");

    *c.ptr() += "-new";
    ASSERT_EQ(*c.ptr(), "TEST-p-new");
}

/// @brief 测试类成员方法的 `const` 修饰符
///
/// 当使用 `const` 修饰类成员方法时, 其表示的是当前对象的状态, 包括:
/// - 无 `const` 修饰或修饰为 `&`, 表示
///
TEST(TEST_SUITE_NAME, const_with_method_for_const_object) {
    const Constant c = Constant("CTEST");
    ASSERT_EQ(c.to_string(), "Constant(CTEST)");

    ASSERT_EQ(c.value(), "TEST-v");

    // c.value() += "-new";

    ASSERT_EQ(c.ref(), "TEST-r");

    // c.ref() += "-new";

    ASSERT_EQ(*c.ptr(), "TEST-p");

    // *c.ptr() += "-new";
}
