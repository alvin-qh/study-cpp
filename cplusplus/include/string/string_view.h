#pragma once

#ifndef __CPLUSPLUS_STRING__STRING_VIEW_H
#define __CPLUSPLUS_STRING__STRING_VIEW_H

#if __ge_cxx17

#include <string_view>

namespace cxx::string {
	using namespace std;

	bool string_compare(const string_view& s1, string_view& s2) {
		return s1.compare(s2) == 0;
	}
}

#endif	// __ge_cxx20

#endif // __CPLUSPLUS_STRING__STRING_VIEW_H
