#if __ge_cxx17

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <any>

#include "../type.h"

#define TEST_SUITE_NAME test_cplusplus_stl_any__make_any

using namespace std;

using testing::ElementsAre;
using cxx::stl::Person;

/// @brief 测试通过类型构造器参数创建 `any` 对象
///
/// 可以通过 `std::any` 对象中实际存储类型的构造器参数, 通过 `make_any(_Args&&... __args)`
/// 函数创建 `std::any` 对象
///
/// `std::any make_any(_Args&&... __args)` 内部调用 `std::any` 的原位构造器创建 `std::any` 对象
TEST(TEST_SUITE_NAME, make_any_by_param) {
    auto a = make_any<int>(1);
    ASSERT_EQ(any_cast<int>(a), 1);

    a = make_any<string>("hello");
    ASSERT_EQ(any_cast<string>(a), string("hello"));

    a = make_any<Person>("Tom", 18, 'M');
    ASSERT_EQ(any_cast<Person>(a), Person("Tom", 18, 'M'));
}

/// @brief 测试通过 `std::initializer_list` 对象构造 `std::any` 对象
///
/// 如果 `std::any` 对象存储类型的构造器具备 `std::initializer_list` 类型参数,
/// 则可通过 `std::any make_any(initializer_list<_Up> __il, _Args&&... __args)` 函数创建 `std::any` 对象
TEST(TEST_SUITE_NAME, make_any_by_initialized_list) {
    any a = make_any<string>({ 'h', 'e', 'l', 'l', 'o' });
    ASSERT_EQ(any_cast<string>(a), "hello");

    a = make_any<vector<int>>({ 1, 2, 3, 4, 5 });
    ASSERT_THAT(any_cast<vector<int>>(a), ElementsAre(1, 2, 3, 4, 5));
}

#endif // __ge_cxx17
