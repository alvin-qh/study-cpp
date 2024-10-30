#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <memory>

#include "stl/optional/optional.h"
#include "../person.h"

#define TEST_SUITE_NAME test_cplusplus_stl_optional__optional

using namespace std;
using namespace cxx::stl;

using testing::ElementsAre;

/// @brief 测试 `optional<T>` 类型对象
TEST(TEST_SUITE_NAME, optional_type) {
    optional<string> opt;

    // 判断 `optional<T>` 类型对象是否有值
    ASSERT_FALSE(opt.has_value());

    opt = "hello";
    ASSERT_TRUE(opt.has_value());

    // 通过 `*` 操作符获取 `optional<T>` 类型对象中存储值的引用
    ASSERT_EQ(*opt, "hello");

    // 通过 `->` 操作符获取 `optional<T>` 类型对象中存储值的指针
    ASSERT_STREQ(opt->c_str(), "hello");

    // 为 `optional<T>` 类型对象设置表示空的对象
    opt = std::nullopt;
    ASSERT_FALSE(opt.has_value());

    opt = "world";

    // 重置 `optional<T>` 类对象, 将其保存的值清空
    opt.reset();
    ASSERT_FALSE(opt.has_value());
}

/// @brief 测试构造器
TEST(TEST_SUITE_NAME, constructors) {
    // 1. 测试 `optional<T>(const T&)` 构造器

    Person ps = Person("Tom", 18, 'M');

    optional<Person> o1(ps);
    ASSERT_TRUE(o1.has_value());
    ASSERT_EQ(*o1, ps);

    // 2. 测试 `optional<T>(T&&)` 构造器

    shared_ptr<Person> p_ps = make_shared<Person>(ps);

    // 通过移动语义, 将参数的右值引用进行传递
    optional<shared_ptr<Person>> o2(std::move(p_ps));
    ASSERT_TRUE(o2.has_value());
    ASSERT_EQ(**o2, ps);

    ASSERT_FALSE(p_ps);

    // 3. 测试 `optional<T>(std::in_place_t, Args&&... args)` 构造器 (原位构造器)

    // 第一个参数固定为 `std::in_place`, 表明要调用原位构造器, 后续参数为 `Person` 类某个构造器的参数
    optional<Person> o3 = optional<Person>(std::in_place, "Tom", 18, 'M');
    ASSERT_TRUE(o3.has_value());
    ASSERT_EQ(*o3, Person("Tom", 18, 'M'));

    // 4. 测试 `optional<T>(std::in_place_t, std::initializer_list<U>, Args&&... args)` 构造器

    // 对于 `T` 类型构造器具备 `std::initializer_list` 参数时, 通过此构造器进行原位构造
    optional<vector<int>> o4 = optional<vector<int>>(std::in_place, { 1, 2, 3, 4, 5 });
    ASSERT_TRUE(o4.has_value());
    ASSERT_THAT(*o4, ElementsAre(1, 2, 3, 4, 5));
}

/// @brief 测试通过 `std::make_optional` 构造对象
TEST(TEST_SUITE_NAME, make_optional) {
    // 1. 测试 `std::make_optional<T>(const T&)` 函数

    Person ps = Person("Tom", 18, 'M');

    auto o1 = make_optional(ps);
    ASSERT_TRUE(o1.has_value());
    ASSERT_EQ(*o1, ps);

    // 2. 测试 `std::make_optional<T>(T&&)` 函数

    shared_ptr<Person> p_ps = make_shared<Person>(ps);

    // 通过移动语义, 将参数的右值引用进行传递
    auto o2 = make_optional(std::move(p_ps));
    ASSERT_TRUE(o2.has_value());
    ASSERT_EQ(**o2, ps);

    ASSERT_FALSE(p_ps);

    // 3. 测试 `std::make_optional<T>(Args&&...)` 函数

    // 该方法内部调用 `optional` 类的原位构造器
    auto o3 = make_optional<Person>("Tom", 18, 'M');
    ASSERT_TRUE(o3.has_value());
    ASSERT_EQ(*o3, Person("Tom", 18, 'M'));

    // 4. 测试 `std::make_optional<T>(std::initializer_list<N>)` 构造器

    // 对于 `T` 类型构造器具备 `std::initializer_list` 参数时, 通过此构造器进行原位构造
    auto o4 = make_optional<vector<int>>({ 1, 2, 3, 4, 5 });
    ASSERT_TRUE(o4.has_value());
    ASSERT_THAT(*o4, ElementsAre(1, 2, 3, 4, 5));
}

/// @brief 测试移动语义
TEST(TEST_SUITE_NAME, move) {
    shared_ptr<Person> ps = make_shared<Person>("Tom", 18, 'M');

    optional<shared_ptr<Person>> o1(ps);
    optional<shared_ptr<Person>> o2(std::move(o1));

    ASSERT_TRUE(*o2);
    ASSERT_EQ(**o2, *ps);

    ASSERT_FALSE(*o1);
}

/// @brief 测试通过函数返回 `optional` 类型对象
TEST(TEST_SUITE_NAME, function_return_value) {
    optional<int> opt = check_even_number(2);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(*opt, 2);

    opt = check_even_number(3);
    ASSERT_FALSE(opt.has_value());
}

TEST(TEST_SUITE_NAME, initializer_list_constructor) {
    optional<int> opt_n{ 42 };
}

