#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
#define __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H

#include <type_traits>
#include <utility>

namespace cpp {
	using namespace std;

	template<typename...T>
	struct make_void {
		using type = void;
	};

	std::is_copy_constructible;

	template<typename...T>
	using void_t = typename make_void<T...>::type;

	template<typename T, typename = void>
	struct has_func : false_type {};

	template<typename T>
	struct has_func<T, void_t<decltype(declval<T>().operator-(declval<T&>()))>> : true_type {};

} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
