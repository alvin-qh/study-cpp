#pragma once

#ifndef __CPLUSPLUS_STRING__STRING_VIEW_H
#define __CPLUSPLUS_STRING__STRING_VIEW_H

#if __ge_cxx17

#include <string_view>
#include <tuple>

namespace cxx::string {
	using namespace std;

	tuple<bool, string_view, string_view> string_compare(const string_view& s1, const string_view& s2) {
		auto r = s1.compare(s2) == 0;
		return make_tuple(r, s1, s2);
	}
}

#endif	// __ge_cxx20

#endif // __CPLUSPLUS_STRING__STRING_VIEW_H
