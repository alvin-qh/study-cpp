#pragma once

#ifndef __CPLUSPLUS_RANGE__TEST_H
#define __CPLUSPLUS_RANGE__TEST_H

#if __ge_cxx20

#include <gmock/gmock.h>

#include <initializer_list>

namespace cxx::ranges {

	/// @brief 断言所给的值是否在指定的列表元素中
	///
	/// @tparam _R 所给值的类型
	/// @tparam _T 列表元素类型
	///
	/// @param r `R` 类型参数
	/// @param vals `T` 类型列表对象
	/// @return 断言结果实例, 表示 `r` 参数是否包含在 `vals` 列表中
	template <typename _R, typename _T>
	testing::AssertionResult rangeOf(_R& r, std::initializer_list<_T>&& vals) {
		auto it = vals.begin();
		for (auto v : r) {
			if (it == vals.end()) {
				return testing::AssertionFailure() << "rangeOf: too many values, ";
			}

			if (v != *it++) {
				return testing::AssertionFailure() << "rangeOf: " << v << " != " << *(--it);
			}
		}
		return testing::AssertionSuccess();
	}
}

#endif // __ge_cxx20

#endif // __CPLUSPLUS_RANGE__TEST_H
