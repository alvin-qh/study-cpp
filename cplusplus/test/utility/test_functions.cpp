#include <gtest/gtest.h>

#include "utility/functions.hpp"

#include <utility>
#include <vector>

#define TEST_SUITE_NAME test_cplusplus_utility_functions

using namespace std;
using namespace cpp::utility;

/// https://learn.microsoft.com/zh-cn/cpp/standard-library/utility-functions?view=msvc-170

/// @brief 测试将可变引用转为只读引用的各类方法
TEST(TEST_SUITE_NAME, as_const) {
	int n = 100;

	// 无法编译通过, 因为传递的 `n` 为非 `const` 引用
	// only_const_reference(n);

	// 通过 `static_cast` 将 `n` 变量转为 `const` 引用, 可通过编译
	only_const_reference(static_cast<const int&>(n));

	// 通过 `const_cast` 将 `n` 变量转为 `const` 引用, 可通过编译
	only_const_reference(const_cast<const int&>(n));

	// 通过 `decltype` 获取 `n` 变量类型, 并通过 `static_cast` 转为 `const` 引用, 可通过编译
	only_const_reference(static_cast<const decltype(n)&>(n));

	// 通过 `remove_reference_t` 获取 `n` 变量的基本类型 (即如果 `n` 为引用类型, 则去掉引用)
	// 通过 `decltype` 获取 `n` 变量类型, 并通过 `add_const_t` 转为 `const` 引用, 可通过编译
	only_const_reference(static_cast<add_const_t<remove_reference_t<decltype(n)>>&>(n));

	// 通过 `as_const` 将 `n` 变量转为 `const` 引用, 可通过编译
	only_const_reference(as_const<int>(n));
}
