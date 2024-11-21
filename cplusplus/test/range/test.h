#pragma once

#ifndef __CPLUSPLUS_RANGE__TEST_H
#define __CPLUSPLUS_RANGE__TEST_H

#if __ge_cxx20

#include <gmock/gmock.h>

#include <initializer_list>

namespace cxx::ranges {

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
