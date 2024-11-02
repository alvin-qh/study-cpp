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
/// 当使用 `const` 修饰类成员方法时, 其表示的是当前对象的状态, 即方法后修饰了 `const`, 
/// 则在方法内部, 相当于当前对象被修饰了 `const`:
/// - 无 `const` 修饰或修饰为 `&` 时, 表示该方法可用于可读写对象 (及引用), 无法用于只读对象 (及引用);
/// - 修饰为 `const` 或修饰为 `const&` 时, 表示该方法可用于可读写对象 (及引用) 以及只读对象 (及引用);
///
/// 修饰为 `const` 的方法表示在方法内部不会对当前对象进行修改
///
/// 对于两个同名, 同参数的方法, 在方法后修饰了 `const` 和未修饰 `const` 的互为重载关系
class Constant {
private:
    string _val, _ref, _ptr;
public:
    /// @brief 参数构造器
    Constant(const string& value) :
        _val(value),
        _ref(value + "-r"),
        _ptr(value + "-p") {
    }

    /// @brief 将当前对象转为字符串
    ///
    /// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
    string to_string() const { return "Constant(" + _val + ")"; }

    /// @brief 重新设置对象字段值
    ///
    /// 该方法未修饰为 `const`, 故仅可被非只读状态的对象调用
    Constant& set(const string& value) {
        _val = value;
        _ref = value + "-r";
        _ptr = value + "-p";
        return *this;
    }

    /// @brief 获取当前对象所存储的值
    ///
    /// 该方法未修饰 `const`, 故无法通过只读对象及其引用 (或指针) 进行调用
    string value() { return _val; }

    /// @brief 获取当前对象所存储的只读值
    ///
    /// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
    ///
    /// 一般情况下, 对于值类型返回值, 无需将返回值修饰为 `const`, 并未实际意义
    const string value() const { return _val; }

    /// @brief 获取当前对象所存储值的指针
    ///
    /// 该方法未修饰 `const`, 故无法通过只读对象及其引用 (或指针) 进行调用
    string* ptr() { return &_ptr; }

    /// @brief 获取当前对象所存储值的只读指针
    ///
    /// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
    ///
    /// 修饰为 `const` 的方法返回的指针类型也必须为 `const`, 表示外部调用此方法时, 
    /// 无法通过返回值对当前对象进行修改
    const string* ptr() const { return &_ptr; }

    /// @brief 获取当前对象所存储值的引用
    ///
    /// 该方法未修饰 `const`, 故无法通过只读对象及其引用 (或指针) 进行调用
    string& ref()& { return _ref; }

    /// @brief 获取当前对象所存储值的只读引用
    ///
    /// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
    ///
    /// 修饰为 `const` 的方法返回的引用类型也必须为 `const`, 表示外部调用此方法时, 
    /// 无法通过返回值对当前对象进行修改
    const string& ref() const& { return _ref; }
};

/// @brief 测试对象在非只读状态下的方法调用情况
TEST(TEST_SUITE_NAME, methods_with_non_const_object) {
    Constant c = Constant("TEST");

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
    const Constant c = Constant("CTEST");

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
    Constant c = Constant("TEST");

    // 产生对象的非只读引用
    Constant& r = c;

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
    const Constant c = Constant("CTEST");

    // 不能用非只读引用引用一个只读对象
    // Constant& r = c;

    // 产生对象的只读引用
    const Constant& r = c;

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
    Constant c = Constant("TEST");

    // 产生对象的非只读指针
    Constant* p = &c;

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
    const Constant c = Constant("CTEST");

    // 不能用非只读指针指向一个只读对象
    // Constant* p = &c;

    // 产生对象的只读指针
    const Constant* p = &c;

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
