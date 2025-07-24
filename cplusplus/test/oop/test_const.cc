#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop__const

#include <string>

#include "oop/const.h"

using namespace std;
using namespace cxx::oop;

/// @brief 测试 `const` 修饰值变量
///
/// 当使用 `const` 修饰值变量时, 表示该变量为只读变量, 不可以修改变量值
TEST(TEST_SUITE_NAME, const_value) {
    const int a = 100;
    ASSERT_EQ(a, 100);

    // 无法修改 const 变量
    // a = 1000;
}

TEST(TEST_SUITE_NAME, global_const_value) {
    // 1. 测试 `constexpr` 修饰的变量
    static_assert(CE_MAX_N == 50);

#if __ge_cxx17
    static_assert(CE_MAX_M == 150);
#endif

#if __ge_cxx20
    static_assert(CE_STR_1 == "Alvin");
#endif

    // 2. 测试 `const` 修饰的变量

    // static_assert(NAME_2 == "Emma");
    ASSERT_EQ(CE_STR_2, "Emma");

    // 一般情况下, 无法修改只读全局变量的值
    // CE_STR_2 = "Lucy";

#ifndef _SANITIZE_LEAK
    // 将只读变量的引用转为可读写变量引用, 并修改变量的值
    const_cast<string&>(CE_STR_2) = "Lucy";
    ASSERT_EQ(CE_STR_2, "Lucy");
#endif
}

#if __ge_cxx17

/// @brief 判断类型是否为整数类型
///
/// 测试常量条件判断, 也即条件分支在编译期就已经确认
///
/// @tparam T 任意类型
template <typename T>
struct integer_test {
    /// @brief 常量函数, 判断 `T` 类型是否为整型
    constexpr static bool test() {
        // 常量分支, 通过 `constexpr` 关键字修饰条件分支,
        // 则条件分支将在编译期进行判断
        if constexpr (
            is_same_v<T, short> ||
            is_same_v<T, int> ||
            is_same_v<T, long> ||
            is_same_v<T, long long> ||
            is_same_v<T, unsigned short> ||
            is_same_v<T, unsigned int> ||
            is_same_v<T, unsigned long> ||
            is_same_v<T, unsigned long long> ||
            is_same_v<T, char> ||
            is_same_v<T, unsigned char>
            ) {
            return true;
        }
        return false;
    }
};

/// @brief 测试常量条件分支
TEST(TEST_SUITE_NAME, const_condition) {
    constexpr int a = 100;

    // 常量分支, 通过 `constexpr` 关键字修饰条件分支,
    // 则条件分支将在编译期进行判断
    if constexpr (a > 50) {
        static_assert(a > 50);
    }
    else {
        // static_assert(a <= 50);
        FAIL();
    }

    int x = 0;
    // 测试模板中使用常量条件分支
    static_assert(integer_test<decltype(x)>().test());
}

#endif // __ge_cxx17

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

/// @brief 测试 `constexpr` 函数作为模板常量参数
///
/// @tparam N 模板常量参数
/// @param n 待比较的参数
/// @return `N` 和 `n` 的值是否相同
template <uint64_t N>
bool check_value(const uint64_t n) {
    // 常量 `N` 无法和变量 `n` 在编译期 (`static_assert`) 进行比较
    // static_assert(N == n);

    // 常量 `N` 无法和变量 `n` 只能在运行期进行比较
    return N == n;
}

/// @brief 测试 `constexpr` 函数在编译期的调用
TEST(TEST_SUITE_NAME, const_function) {
    // 调用常量函数, 返回的结果也是常量, 该函数在编译期完成调用
    constexpr uint64_t cr = const_fib(25);
    static_assert(cr == 75025);

    // 常量函数的结果可以作为模板常量参数
    uint64_t r = check_value<const_fib(10)>(55);
    ASSERT_TRUE(r);

    // 对于过于复杂的调用 (函数内部复杂或者函数递归调用),
    // 则无法在编译期处理为常量
    // constexpr uint64_t cr = const_fib(30);

    // 过于复杂的常量函数, 只能在运行期调用, 不在作为常量函数
    uint64_t rr = const_fib(30);
    ASSERT_EQ(rr, 832040);
}

/// @brief 测试常量类
TEST(TEST_SUITE_NAME, const_class) {
    // 实例后常量类对象, 该对象为一个常量值
    // 常量类对象的实例化在编译期进行
    // 常量类对象的实例化需要配合 `static`
    static constexpr ConstClass c1 = ConstClass("A", 100);

    // 调用常量类对象的方法, 这些方法均为常量方法, 可以在编译期调用执行
    static_assert(c1.name() == "A");
    static_assert(c1.value() == 100);

    // 在运行期也可以调用常量类型对象的方法, 这些方法将被编译为常量值
    ASSERT_EQ(c1.name(), "A");
    ASSERT_EQ(c1.value(), 100);

    ConstClass c2 = ConstClass("B", 200);
    // static_assert(c2.name() == "B");
    ASSERT_EQ(c2.name(), "B");
    ASSERT_EQ(c2.value(), 200);
}

/// @brief 测试类中的常量成员字段
TEST(TEST_SUITE_NAME, const_class_field) {
    // 1. 测试 `constexpr static` 类成员字段

    // 修饰为 `constexpr static` 的类成员字段表示一个常量, 可在编译期访问
    // 测试数组类型常量成员字段
    static_assert(static_str_cmp(ConstField::CES_CSTR, "A") == 0);

#if __ge_cxx20
    // 测试字符串类型常量成员字段
    static_assert(ConstField::CES_STR == "B");
#endif

    // 测试结构体类型常量成员字段
    static_assert(ConstField::CES_STRUCT.name == "C");
    static_assert(ConstField::CES_STRUCT.value == 20);

    // 测试对象类型常量成员字段
    static_assert(ConstField::CES_CLASS.name() == "D");
    static_assert(ConstField::CES_CLASS.value() == 100);

    // 2. 测试 `const` 类成员字段

    ConstField cf;

    // 类的只读字段必须通过对应的类对象访问, 且只能在运行期访问
    // static_assert(cf.c_str_1 == "BB");
    ASSERT_EQ(cf.c_str_1, "AA");

    // 一般情况下, 无法修改只读字段的值
    // cf.c_str = "AAA";

#if __ge_cxx20
    // 可通过类型转化将只读字段 (的引用) 转为可读写字段 (的引用)
    // 通过转换后的结果, 即可为只读字段重新赋值
    const_cast<string&>(cf.c_str_1) = "AAA";
    ASSERT_EQ(cf.c_str_1, "AAA");
#else
    ASSERT_STREQ(cf.c_str_1, "AA");
#endif

    // 3. 测试 `const static` 类成员字段

    // static_assert(ConstField::c_str_2 == "BB");
    ASSERT_EQ(ConstField::CS_STR_2, "BB");

#ifndef _SANITIZE_LEAK
    // 通过 `const_cast` 将只读变量转为可读引用
    const_cast<string&>(ConstField::CS_STR_2) = "BBB";
    ASSERT_EQ(ConstField::CS_STR_2, "BBB");
#endif
}

/// @brief 测试对象在非只读状态下的方法调用情况
TEST(TEST_SUITE_NAME, methods_with_non_const_object) {
    ConstMethod c = ConstMethod("TEST");

    // 对于修饰为 `const` 的方法, 非只读状态的对象可以正常调用
    ASSERT_EQ(c.to_string(), "Constant(TEST)");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象可以正常调用
    ASSERT_EQ(c.value(), "TEST");

    // 返回值非只读状态, 可以对其进行修改, 但由于返回的是值类型,
    // 故改修改不会影响到对象本身
    c.value() += "-new";
    ASSERT_EQ(c.value(), "TEST");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象可以正常调用
    ASSERT_EQ(c.ref(), "TEST-r");

    // 返回值非只读状态, 可以对其进行修改, 且由于返回的是引用,
    // 故修改会影响到对象本身
    c.ref() += "-new";
    ASSERT_EQ(c.ref(), "TEST-r-new");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象可以正常调用
    ASSERT_EQ(*c.ptr(), "TEST-p");

    // 返回值非只读状态, 可以对其进行修改, 且由于返回的是指针,
    // 故修改会影响到对象本身
    *c.ptr() += "-new";
    ASSERT_EQ(*c.ptr(), "TEST-p-new");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象可以正常调用
    c.set("TEST-2");
    ASSERT_EQ(c.value(), "TEST-2");
}

/// @brief 测试对象在只读状态下的方法调用情况
TEST(TEST_SUITE_NAME, methods_with_const_object) {
    const ConstMethod c = ConstMethod("CTEST");

    // 对于修饰为 `const` 的方法, 只读状态的对象可以正常调用
    ASSERT_EQ(c.to_string(), "Constant(CTEST)");

    // 对于只读状态的对象, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(c.value(), "CTEST");

    // 方法返回的为 `const` 值, 故无法对其进行修改
    // c.value() += "-new";

    // 对于只读状态的对象, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(c.ref(), "CTEST-r");

    // 方法返回的为 `const` 引用, 故无法对其进行修改
    // c.ref() += "-new";

    // 对于只读状态的对象, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(*c.ptr(), "CTEST-p");

    // 方法返回的为 `const` 指针, 故无法对其进行修改
    // *c.ptr() += "-new";

    // 无法对只读对象调用未修饰 `const` 的方法
    // c.set("CTEST-2");
}

/// @brief 测试通过对象的非只读引用进行的方法调用情况
TEST(TEST_SUITE_NAME, methods_with_non_const_object_ref) {
    ConstMethod c = ConstMethod("TEST");

    // 产生对象的非只读引用
    ConstMethod& r = c;

    // 对于修饰为 `const` 的方法, 非只读状态的对象引用可以正常调用
    ASSERT_EQ(r.to_string(), "Constant(TEST)");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象引用可以正常调用
    ASSERT_EQ(r.value(), "TEST");

    // 返回值非只读状态, 可以对其进行修改, 但由于返回的是值类型,
    // 故改修改不会影响到对象本身
    r.value() += "-new";
    ASSERT_EQ(c.value(), "TEST");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象引用可以正常调用
    ASSERT_EQ(r.ref(), "TEST-r");

    // 返回值非只读状态, 可以对其进行修改, 且由于返回的是引用,
    // 故修改会影响到对象本身
    r.ref() += "-new";
    ASSERT_EQ(c.ref(), "TEST-r-new");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象引用可以正常调用
    ASSERT_EQ(*r.ptr(), "TEST-p");

    // 返回值非只读状态, 可以对其进行修改, 且由于返回的是指针,
    // 故修改会影响到对象本身
    *r.ptr() += "-new";
    ASSERT_EQ(*c.ptr(), "TEST-p-new");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象引用可以正常调用
    r.set("TEST-2");
    ASSERT_EQ(c.value(), "TEST-2");
}

/// @brief 测试通过对象的只读引用进行的方法调用情况
TEST(TEST_SUITE_NAME, methods_with_const_object_ref) {
    const ConstMethod c = ConstMethod("CTEST");

    // 不能用非只读引用引用一个只读对象
    // Constant& r = c;

    // 产生对象的只读引用
    const ConstMethod& r = c;

    // 对于修饰为 `const` 的方法, 只读状态的对象引用可以正常调用
    ASSERT_EQ(r.to_string(), "Constant(CTEST)");

    // 对于只读状态的对象, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(r.value(), "CTEST");

    // 方法返回的为 `const` 值, 故无法对其进行修改
    // r.value() += "-new";

    // 对于只读状态的对象引用, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(r.ref(), "CTEST-r");

    // 方法返回的为 `const` 引用, 故无法对其进行修改
    // r.ref() += "-new";

    // 对于只读状态的对象引用, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(*r.ptr(), "CTEST-p");

    // 方法返回的为 `const` 指针, 故无法对其进行修改
    // *r.ptr() += "-new";

    // 无法对只读状态的对象引用调用未修饰 `const` 的方法
    // r.set("CTEST-2");
}

/// @brief 测试通过对象的非只读指针进行的方法调用情况
TEST(TEST_SUITE_NAME, methods_with_non_const_object_ptr) {
    ConstMethod c = ConstMethod("TEST");

    // 产生对象的非只读指针
    ConstMethod* p = &c;

    // 对于修饰为 `const` 的方法, 非只读状态的对象指针可以正常调用
    ASSERT_EQ(p->to_string(), "Constant(TEST)");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象指针可以正常调用
    ASSERT_EQ(p->value(), "TEST");

    // 返回值非只读状态, 可以对其进行修改, 但由于返回的是值类型,
    // 故改修改不会影响到对象本身
    p->value() += "-new";
    ASSERT_EQ(c.value(), "TEST");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象指针可以正常调用
    ASSERT_EQ(p->ref(), "TEST-r");

    // 返回值非只读状态, 可以对其进行修改, 且由于返回的是引用,
    // 故修改会影响到对象本身
    p->ref() += "-new";
    ASSERT_EQ(c.ref(), "TEST-r-new");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象指针可以正常调用
    ASSERT_EQ(*p->ptr(), "TEST-p");

    // 返回值非只读状态, 可以对其进行修改, 且由于返回的是指针,
    // 故修改会影响到对象本身
    *p->ptr() += "-new";
    ASSERT_EQ(*c.ptr(), "TEST-p-new");

    // 对于未修饰为 `const` 的方法, 非只读状态的对象指针可以正常调用
    p->set("TEST-2");
    ASSERT_EQ(c.value(), "TEST-2");
}

/// @brief 测试通过对象的只读指针进行的方法调用情况
TEST(TEST_SUITE_NAME, methods_with_const_object_ptr) {
    const ConstMethod c = ConstMethod("CTEST");

    // 不能用非只读指针指向一个只读对象
    // Constant* p = &c;

    // 产生对象的只读指针
    const ConstMethod* p = &c;

    // 对于修饰为 `const` 的方法, 只读状态的对象指针可以正常调用
    ASSERT_EQ(p->to_string(), "Constant(CTEST)");

    // 对于只读状态的对象, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(p->value(), "CTEST");

    // 方法返回的为 `const` 值, 故无法对其进行修改
    // p->value() += "-new";

    // 对于只读状态的对象指针, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(p->ref(), "CTEST-r");

    // 方法返回的为 `const` 引用, 故无法对其进行修改
    // r.ref() += "-new";

    // 对于只读状态的对象指针, 只能访问其后修饰了 `const` 的方法
    ASSERT_EQ(*p->ptr(), "CTEST-p");

    // 方法返回的为 `const` 指针, 故无法对其进行修改
    // *p->ptr() += "-new";

    // 无法对只读对象指针调用未修饰 `const` 的方法
    // p->set("CTEST-2");
}
