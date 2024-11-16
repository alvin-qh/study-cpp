/// `std::string_view`
///
/// 对于 C++ 的 `std::string` 类型来说, 其内容可变, 且每次对象的每次赋值都会发生内存拷贝,
/// 产生新的对象, 这就导致在很多场景下 (只对字符串进行读操作, 且需要在变量间进行复制),
/// `std::string` 会带来效率的损失;
///
/// `std::string_view` 类型则不存在此问题, 其存储一个只读字符串的引用,
/// 且在变量中赋值不会进行实质性的内存拷贝, 适合解决上述 `std::string` 类型带来的性能问题

#if __ge_cxx17

#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <array>
#include <climits>
#include <string_view>

#include "string/string_view.h"

#define TEST_SUITE_NAME test_cplusplus_string__string_view

using namespace std;
using namespace cxx::string;

/// @brief 测试构造器
TEST(TEST_SUITE_NAME, constructor) {
    // 1. 通过字符串常量指针创建对象
    string_view sv1("hello world");
    ASSERT_EQ(sv1, "hello world");

    // 2. 通过字符串常量指针以及指定长度创建对象
    const char* ps = "hello world";

    string_view sv2(ps, 5);
    ASSERT_EQ(sv2, "hello");

    // 3. 拷贝构造器
    string_view sv3(sv2);
    ASSERT_EQ(sv3, "hello");

    // 4. 通过迭代器创建对象
    vector<char> vec = { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd' };

    string_view sv5(vec.begin(), vec.end());
    ASSERT_EQ(sv5, "hello world");

    // 对于非 `random_iterator`, 无法用于初始化 `string_view` 对象
    // list<char> lst = { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd' };
    // string_view sv6(lst.begin(), lst.end());
}

/// @brief 测试赋值运算符
///
/// `std::string_view` 的一个优势即可以低成本的进行赋值:
/// 1. 当 `std::string_view` 的赋值发生时, 仅是内部指向字符串的指针值发生了复制,
///    字符串内容并未发生复制;
/// 2. `std::string_view` 对象内部的字符串指针可以指向任意字符的任意部分,
///    产生新的 `std::string_view` 对象
TEST(TEST_SUITE_NAME, assignment) {
    string_view sv1("hello world"), sv2;

    // 对象赋值
    sv2 = sv1;

    // 确认赋值前后两个对象保存着相同的字符串指针
    ASSERT_EQ(sv1.data(), sv2.data());
    ASSERT_EQ(sv2, "hello world");

    // 令 `std::string_view` 内部指针指向其自身 6 字节后,
    // 确认 `std::string_view` 对象的内容发生变化
    sv2 = sv2.substr(6);
    ASSERT_EQ(sv1.data() + 6, sv2.data());
    ASSERT_EQ(sv2, "world");

    // `std::string_view` 的赋值运算符仅接受同为 `std::string_view` 类型对象作为参数,
    // 所以当赋值运算符的参数不为 `std::string_view` 类型时,
    // 则编译期会自动将参数类型转为 `std::string_view` 类型

    // 自动将参数类型从 `const char*` 类型转为 `std::string_view` 类型后进行赋值
    sv2 = "Hello";
    ASSERT_EQ(sv2, "Hello");

    // 自动将参数类型从 `std::string` 类型转为 `std::string_view` 类型后进行赋值,
    // 但由于 `std::string` 对象的生命周期很短, 导致`std::string_view`
    // 对象完成赋值后失效, 无法使用
    sv2 = static_cast<string>("Hello");
    // ASSERT_EQ(sv2, "Hello");
}

/// @brief 测试 `std::string_view` 对象内部字符串引用情况
///
/// `std::string_view` 之所以在赋值时具备更好的效率, 源于其并未真正分配内存存储字符串数据,
/// 而是保存了原始存放字符串内存的地址
///
/// 所以, 当传递给 `std::string_view` 对象地址指向的内容发生变化, 则 `std::string_view`
/// 所表示的字符串内容也会相应变化
TEST(TEST_SUITE_NAME, reference) {
    // 1. 测试对 `std::string` 对象的引用情况
    string str = "hello world";

    // 通过 `std::string` 字符串构建对象
    string_view sv1(str);

    // 确认 `std::string_view` 内部字符串地址和 `std::string`
    // 的内部字符串指针地址一致
    ASSERT_EQ(sv1.data(), str.c_str());

    // 改变 `std::string` 字符串的内容, 确认 `std::string_view`
    // 内部字符串指针指向的内容同样发生变化
    str.clear();
    ASSERT_STREQ(sv1.data(), "");

    // 2. 测试对 `char*` 的引用情况
    char* ps = new char[] {"hello world"};

    // 通过 `char*` 字符串指针构建对象
    string_view sv2(ps);

    // 确认 `std::string_view` 内部字符串地址和字符串指针地址一致
    ASSERT_EQ(sv2.data(), ps);
    ASSERT_EQ(sv2, "hello world");

    // 改变字符串指针指向字符串的内容, 确认 `std::string_view` 对象的内容随之改变
    ps[0] = 'H';
    ASSERT_EQ(sv2, "Hello world");

    delete[] ps;

    // 3. 测试对数组的引用
    auto arr = to_array({ 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd' });

    // 通过数组构建对象
    string_view sv3(arr.data(), arr.size());

    // 确认 `std::string_view` 内部字符串地址和数组的指针一致
    ASSERT_EQ(sv3.data(), arr.data());
    ASSERT_EQ(sv3, "hello world");

    // 改变数组内容, 确认 `std::string_view` 对象的内容随之改变
    arr[0] = 'H';
    ASSERT_EQ(sv3, "Hello world");

    // 4. 测试通过迭代器对原集合的引用
    vector<char> vec = { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd' };

    // 通过向量对象迭代器创建对象
    string_view sv4(vec.begin(), vec.end());

    // 确认 `std::string_view` 内部字符串地址和向量对象内部数据指针地址一致
    ASSERT_EQ(sv4.data(), vec.data());
    ASSERT_EQ(sv4, "hello world");

    // 改变向量内容, 确认 `std::string_view` 对象的内容随之改变
    vec[0] = 'H';
    ASSERT_EQ(sv4, "Hello world");
}

/// @brief 测试对象的生命周期
///
/// `std::string_view` 对象引用的字符串指针指向的内存一旦被销毁, 则 `std::string_view`
/// 对象表示的字符串也将失效, 故而 `std::string_view`
/// 对象的生命周期不得大于传递给其的字符串指针的生命周期, 所以 `std::string_view`
/// 不适合作为长期对象, 只适合在局部范围内 (例如一个函数参数) 短期存在
TEST(TEST_SUITE_NAME, lifecycle) {
    // 测试使用临时变量构建 `std::string_view` 对象, 得到无效对象
    string_view sv(static_cast<string>("hello world"));
    // ASSERT_EQ(sv, "hello world");

    // 测试使用临时内存构建 `std::string_view` 对象, 当临时内存回收后, `std::string_view` 对象失效
    char* p = new char[] {"hello world"};
    sv = p;
    // ASSERT_EQ(sv, "hello world");
    delete[] p;

    // 在有限的作用域范围内使用 `std::string_view` 对象,
    // 对于 `string_compare` 函数的两个 `std::string_view` 类型参数, 第一个参数引用了字符串常量,
    // 第二个参数引用了临时字符串对象, 故 `string_compare` 函数返回的第二个 `std::string_view`
    // 对象无效
    auto r = string_compare("Hello", string("hello"));
    ASSERT_FALSE(get<0>(r));
    ASSERT_EQ(get<1>(r), "Hello");
    // ASSERT_EQ(get<2>(r), "hello");
}

/// @brief 测试迭代器
///
/// `std::string_view` 和 `std::string` 类型的迭代器方法一致, 包括 `begin` 与 `end` 方法,
/// `cbegin` 与 `cend` 方法, `regin` 与 `rend` 方法以及 `crbegin` 与 `crend` 方法;
///
/// 由于 `std::string_view` 的不可变特性, 故只能获取到只读迭代器, 所以 `begin` 及 `cbegin` 方法一致,
/// `end` 及 `cend` 方法一致, `rbegin` 及 `crbegin` 方法一致, `rend` 及 `crend` 方法一致
TEST(TEST_SUITE_NAME, iterator) {
    string_view sv("hello world");

    size_t i = 0;

    // 1. 测试正向迭代器, 其为只读迭代器
    for (auto it = sv.begin(); it != sv.end(); ++it) {
        ASSERT_EQ(sv[i++], *it);

        // 迭代器为只读迭代器
        // *it = 'x';
    }

    i = 0;

    // 2. 测试正向只读迭代器
    for (auto it = sv.cbegin(); it != sv.cend(); ++it) {
        ASSERT_EQ(sv[i++], *it);
    }

    i = sv.length() - 1;

    // 3. 测试反向迭代器, 其为只读迭代器
    for (auto it = sv.rbegin(); it != sv.rend(); ++it) {
        ASSERT_EQ(sv[i--], *it);

        // 迭代器为只读迭代器
        // *it = 'x';
    }

    i = sv.length() - 1;

    // 4. 测试反向只读迭代器
    for (auto it = sv.crbegin(); it != sv.crend(); ++it) {
        ASSERT_EQ(sv[i--], *it);
    }

    i = 0;

    // 5. 测试迭代器的 `for in` 循环
    for (auto c : sv) {
        ASSERT_EQ(sv[i++], c);
    }
}

/// @brief 获取指定位置的字符值
///
/// 通过 `std::string_view` 对象的 `at` 方法或 `operator[]` 操作符用于获取指定位置的字符
TEST(TEST_SUITE_NAME, character_at) {
    string_view sv("hello world");

    ASSERT_EQ(sv.at(0), 'h');
    ASSERT_EQ(sv.at(sv.length() - 1), 'd');

    ASSERT_EQ(sv[0], 'h');
    ASSERT_EQ(sv[sv.length() - 1], 'd');
}

/// @brief 获取第一个以及最后一个字符
TEST(TEST_SUITE_NAME, front_back) {
    string_view sv("hello world");

    ASSERT_EQ(sv.front(), 'h');
    ASSERT_EQ(sv.back(), 'd');
}

/// @brief 获取对象内部指向字符串的指针
TEST(TEST_SUITE_NAME, data) {
    const char* ps = "hello world";

    string_view sv(ps);
    ASSERT_EQ(sv.data(), ps);
    ASSERT_STREQ(sv.data(), "hello world");
}

/// @brief 获取对象引用的字符串是否为空
TEST(TEST_SUITE_NAME, empty) {
    string_view sv = "hello world";
    ASSERT_FALSE(sv.empty());

    sv = "";
    ASSERT_TRUE(sv.empty());
}

/// @brief 获取字符串长度
///
/// 通过 `length` 以及 `size` 方法可以获取 `std::string_view` 对象引用的字符串的长度,
/// 两个方法的作用一致;
///
/// 而 `max_size` 方法返回一个常量, 表示当前对象可以引用字符串的最长长度
TEST(TEST_SUITE_NAME, size_and_length) {
    string_view sv = "hello world";

    ASSERT_EQ(sv.length(), sv.size());
    ASSERT_EQ(sv.length(), 11);
    ASSERT_EQ(sv.size(), 11);

    static_assert(sv.max_size() == 4611686018427387899L);
}

/// @brief 移除字符串前或后指定长度的内容
///
/// `std::string_view` 对象通过移动内部的字符串指针值以达到从前或后移除指定长度字符的目标
///
/// 如果删除的字符数大于字符串本身的长度, 则会在导致 `std::string_view` 对象失效
TEST(TEST_SUITE_NAME, remove_prefix_or_suffix) {
    const char* ps = "+++A---";

    string_view sv(ps);
    ASSERT_EQ(sv.size(), 7);

    // 1. 从前面删除 3 个字符
    sv.remove_prefix(3);
    ASSERT_EQ(sv.size(), 4);

    // 相当于将内部头指针向后移动 3 个单位
    ASSERT_EQ(sv.data() - 3, ps);
    ASSERT_EQ(sv, "A---");

    // 2. 从后面删除 3 个字符
    sv.remove_suffix(3);
    ASSERT_EQ(sv.size(), 1);

    // 相当于将内部尾指针向前移动 3 个字节
    ASSERT_EQ(sv.data() - 3, ps);
    ASSERT_EQ(sv, "A");

    // 当 `remove_prefix` 和 `remove_suffix` 方法参数值大于字符串本身长度,
    // 则会令 `std::string_view` 对象失效
    sv.remove_prefix(2);
    // ASSERT_EQ(sv, "");
}

#endif // __ge_cxx17