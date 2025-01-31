#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop__casting

/// @brief 用于测试指针转换的父类
class A {
protected:
    int _id;

    A(int id) : _id(id) { }
public:
    A() : A(100) { }
    virtual const char* who_am_i() const noexcept { return "class A"; }
    virtual int id() const { return _id; }
};

/// @brief 用于测试指针转换的子类
class B : public A {
public:
    B() : A(200), _tag(10) { }
    virtual const char* who_am_i() const noexcept override { return "class B"; }
    virtual int tag() const { return _tag; }

private:
    int _tag;
};

/// @brief 测试静态类型转换
///
/// `static_cast` 操作符的作用包括:
///
/// 1. 基本类型之间进行转换
/// 2. `void*` 指针到任意类型指针的转换;
/// 3. 具备继承关系的子类与父类指针 (或引用) 的转换
///
/// `static_cast` 在进行父类和子类指针转换时, 并不会检查指针指向的实际类型, 故可能会导致转换错误
TEST(TEST_SUITE_NAME, static_casting) {
    // `int` => `double`
    // 这是 `static_cast` 最基本的用法, 即基本类型值之间的转换,
    // 相当于 C 语音的强制转换, 例如: `int a = 10; double d = (double) a;`
    int n = 100;
    double f = static_cast<double>(n);

    // `int*` => `double*`
    // `static_cast` 可以将 `void*` 指针转为任何类型指针, 但不保证转换合法,
    // 例如本例中, `int*` 转为 `double*` 是不合法的, 两种类型的内存存储方式不同,
    // 但 `static_cast` 仍可成功进行转换
    int* pn = &n;
    double* pf = static_cast<double*>(static_cast<void*>(pn));
    // ASSERT_NE(*pf, n);

    B b;

    // `B*` => `A*`
    // 将子类指针转为父类指针
    // 通过 `static_cast` 可以将子类型指针转为父类型指针, 相当于 C 语音的强制转换:
    // `B b; A* pa = &b`
    A* pa = static_cast<A*>(&b);
    ASSERT_EQ(pa->who_am_i(), "class B");
    ASSERT_EQ(pa->id(), 200);

    A a;

    // `A*` => `B*`, 将父类指针转为子类指针
    // 将父类指针转为子类指针, 转换过程中不会进行检测
    // 除非父类型指针指向的本身就是子类型实例, 否则将父类型指针转为子类型是不合法的
    B* pb = static_cast<B*>(&a);
    ASSERT_EQ(pb->who_am_i(), "class A");
    ASSERT_EQ(pb->id(), 100);
    // ASSERT_EQ(pb->tag(), 10); // 父类实例中不存在 `_tag` 成员和 `tag` 方法, 执行过程中会报错
}

/// @brief 动态指针类型转换
///
/// `dynamic_cast` 操作符用于指针类型转换, 主要指的是父子类型指针之间的转换;
/// 所谓动态类型转换, 指的是在运行时通过 C++ 的 RTTI 特性进行类型检查,
/// 如果转换成立, 则完成转换, 否则返回 `nullptr` 表示转换失败
///
/// `dynamic_cast` 操作符在执行过程中会检查目标指针类型和指针指向的对象实际类型,
/// 如果指针指向的是父类对象, 但目标是转换为子类指针, 则转换会失败
TEST(TEST_SUITE_NAME, dynamic_casting_for_pointer) {
    B b;

    // `B*` => `A*`
    // 将子类指针转为父类指针
    A* pa = dynamic_cast<A*>(&b);
    ASSERT_NE(pa, nullptr);
    ASSERT_EQ(pa->who_am_i(), "class B");
    ASSERT_EQ(pa->id(), 200);

    // `A*` => `B*`
    // 本例中, 由于 `A*` 类型指针实际指向的是 `B` 类型对象,
    // 故可以将 `A*` 类型指针转为 `B*` 类型指针
    B* pb = dynamic_cast<B*>(pa);
    ASSERT_NE(pb, nullptr);
    ASSERT_EQ(pb->who_am_i(), "class B");
    ASSERT_EQ(pb->id(), 200);
    ASSERT_EQ(pb->tag(), 10);

    A a;

    // `A*` => `B*`
    // 本例中, 由于 `A*` 类型指针实际指向的就是 `A` 类型对象,
    // 故将 `A*` 类型指针转为 `B*` 类型指针不合法, 转换失败,
    // 返回 `nullptr` 结果
    pb = dynamic_cast<B*>(&a);
    ASSERT_EQ(pb, nullptr);
}

/// @brief 动态引用类型转换
///
/// `dynamic_cast` 也可以对引用类型进行转换, 规则和指针类型转换一致;
/// 由于引用类型不能为 "空", 故 `dynamic_cast` 在转换引用失败后,
/// 会抛出 `std::bad_cast&` 异常
TEST(TEST_SUITE_NAME, dynamic_casting_for_reference) {
    B b;

    // `B&` => `A&`
    // 将子类引用转为父类引用
    A& ra = dynamic_cast<A&>(b);
    ASSERT_EQ(ra.who_am_i(), "class B");
    ASSERT_EQ(ra.id(), 200);

    // `A&` => `B&`
    // 本例中, 由于 `A&` 类型引用实际引用的是 `B` 类型对象,
    // 故可以将 `A&` 类型引用转为 `B&` 类型引用
    B& rb = dynamic_cast<B&>(ra);
    ASSERT_EQ(rb.who_am_i(), "class B");
    ASSERT_EQ(rb.id(), 200);
    ASSERT_EQ(rb.tag(), 10);

#ifndef _SANITIZE_LEAK
    A a;

    // `A&` => `B&`
    // 本例中, 由于 `A&` 类型引用实际引用的就是 `A` 类型对象,
    // 故将 `A&` 类型引用转为 `B&` 类型引用不合法, 转换失败,
    // 抛出 `std::bad_cast&` 异常
    try {
        B& _ = dynamic_cast<B&>(a);
        FAIL();
    }
    catch (std::bad_cast& e) {
        ASSERT_STREQ(e.what(), "std::bad_cast");
    }
#endif
}

/// @brief 只读/可变指针类型转换
TEST(TEST_SUITE_NAME, const_casting_for_pointer) {
    const int a = 100;

    // 定义只读指针, 指向 a 变量
    const int* pa = &a;
    // *pca = 200; // 只读指针无法进行修改

    // 将只读指针转为可变指针, 修改其指向的值
    *const_cast<int*>(pa) = 200;
    ASSERT_EQ(a, 200);
}

/// @brief 只读/可变引用类型转换
TEST(TEST_SUITE_NAME, const_casting_for_reference) {
    const int a = 100;

    // 定义只读引用, 指向 a 变量
    const int& ra = a;
    // ra = 200; // 只读引用无法进行修改

    // 将只读引用转为可变引用, 修改其引用的值
    const_cast<int&>(ra) = 200;
    ASSERT_EQ(a, 200);
}

/// @brief 强制指针类型转换
///
/// `reinterpret_cast` 相当于强制指针类型转换, 可以在任意指针类型之间进行转换, 包括:
/// 1. 将任意指针值转为整数 (`uintptr_t` 类型);
/// 2. 将某个类型的指针值转为任意其它类型指针值;
///
/// 注意: `reinterpret_cast` 转换完全不保证合法性, 需开发人员自行保证转换合法
TEST(TEST_SUITE_NAME, reinterpret_casting) {
    int a = 100;

    // 将指针类型转为整数值
    uintptr_t n = reinterpret_cast<uintptr_t>(&a);

    // 将整数转为指针类型
    int* pa = reinterpret_cast<int*>(n);
    ASSERT_EQ(*pa, a);

    // 在不同类型指针之间相互转换
    long long* pl = reinterpret_cast<long long*>(pa);
    pa = reinterpret_cast<int*>(pl);
    ASSERT_EQ(*pa, a);
}
