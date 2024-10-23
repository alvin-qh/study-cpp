#pragma once

#ifndef __CPLUSPLUS_ITERATOR_CONCEPT_H
#define __CPLUSPLUS_ITERATOR_CONCEPT_H

#include <iterator>

namespace cpp::iter {

	template <typename _Iter>
		requires std::input_or_output_iterator<_Iter>
	void need_input_or_output_iterator(_Iter it) {}

	template <typename _Iter>
		requires std::forward_iterator<_Iter>
	void need_forward_iterator(_Iter it) {}

	template <typename _Iter>
		requires std::bidirectional_iterator<_Iter>
	void need_bidirectional_iterator(_Iter it) {}

	template <typename _Iter>
		requires std::random_access_iterator<_Iter>
	void need_random_access_iterator(_Iter it) {}
}

#endif // ! __CPLUSPLUS_ITERATOR_CONCEPT_H
