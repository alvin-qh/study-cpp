#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
#define __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H

namespace cpp {
	using namespace std;

	template<typename...T>
	struct make_void {
		using type = void;
	};

	template<typename...T>
	using void_t = typename make_void<T...>::type;

	template<typename T, typename = void>
	struct has_operator_sub : false_type {};

	template<typename T>
	struct has_operator_sub<T, void_t<decltype(declval<T>().operator-(declval<T&>()))>> : true_type {};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEMPLATE_TYPE_DETECT_H
