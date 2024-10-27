#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "stl/optional/optional.h"

#define TEST_SUITE_NAME test_cplusplus_stl_optional__optional

using namespace std;
using namespace cxx::stl;

/// @brief 测试 `optional<T>` 类型对象
TEST(TEST_SUITE_NAME, optional_type) {
    optional<int> opt;

    // 判断 `optional<T>` 类型对象是否有值
    ASSERT_FALSE(opt.has_value());

    opt = 42;
    ASSERT_TRUE(opt.has_value());

    // 通过 `*` 操作符获取 `optional<T>` 类型对象中存储的值
    ASSERT_EQ(*opt, 42);

    // 为 `optional<T>` 类型对象设置表示空的对象
    opt = std::nullopt;
    ASSERT_FALSE(opt.has_value());

    opt = 200;

    // 重置 `optional<T>` 类对象, 将其保存的值清空
    opt.reset();
    ASSERT_FALSE(opt.has_value());
}

TEST(TEST_SUITE_NAME, optional_return_value) {
    optional<int> opt = check_even_number(2);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(*opt, 2);

    opt = check_even_number(3);
    ASSERT_FALSE(opt.has_value());
}

class Person {
private:
    string _name;
    uint8_t _age;
    char _gender;

    bool __eq(const Person& o) const {
        return _name == o._name &&
            _age == o._age &&
            _gender == o._gender;
    }
public:
    Person(const string& name, uint8_t age, char gender) :
        _name(name), _age(age), _gender(gender) {
    }

    Person(string&& name, uint8_t age, char gender) :
        _name(std::forward<string>(name)), _age(age), _gender(gender) {
    }

    const string& name() const { return _name; }

    uint8_t age() const { return _age; }

    char gender() const { return _gender; }

    bool operator==(const Person& o) const { return this == &o || __eq(o); }
};

TEST(TEST_SUITE_NAME, initializer_list_constructor) {
    optional<int> opt_n{ 42 };
}

TEST(TEST_SUITE_NAME, make_optional) {
    auto opt_n = make_optional<int>(42);
    ASSERT_TRUE(opt_n.has_value());
    ASSERT_EQ(*opt_n, 42);

    auto opt_p = make_optional<Person>("Tom", 18, 'M');
    ASSERT_TRUE(opt_p.has_value());
    ASSERT_EQ(*opt_p, Person("Tom", 18, 'M'));
}
