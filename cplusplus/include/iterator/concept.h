#pragma once

#ifndef __CPLUSPLUS_ITERATOR__CONCEPT_H
#define __CPLUSPLUS_ITERATOR__CONCEPT_H

#include <iterator>

namespace cxx::iterator {

#if __ge_cxx20

	/// @brief 检测迭代器是否为 `input iterator` 或 `output iterator` 迭代器
	template <typename _Iter>
	constexpr bool is_input_or_output_iterator(_Iter) noexcept { return false; }

	template <typename _Iter>
		requires std::input_or_output_iterator<_Iter>
	constexpr bool is_input_or_output_iterator(_Iter) noexcept { return true; }

	// --------------------------------------------------------------------------

	/// @brief 检测迭代器是否为 `forward iterator` 迭代器
	template <typename _Iter>
	constexpr bool is_forward_iterator(_Iter) noexcept { return false; }

	template <typename _Iter>
		requires std::forward_iterator<_Iter>
	constexpr bool is_forward_iterator(_Iter) noexcept { return true; }

	// --------------------------------------------------------------------------

	/// @brief 检测迭代器是否为 `bidirectional iterator` 迭代器
	template <typename _Iter>
	constexpr bool is_bidirectional_iterator(_Iter) noexcept { return false; }

	template <typename _Iter>
		requires std::bidirectional_iterator<_Iter>
	constexpr bool is_bidirectional_iterator(_Iter) noexcept { return true; }

	// --------------------------------------------------------------------------

	/// @brief 检测迭代器是否为 `random access iterator` 迭代器
	template <typename _Iter>
	constexpr bool is_random_access_iterator(_Iter) noexcept { return false; }

	template <typename _Iter>
		requires std::random_access_iterator<_Iter>
	constexpr bool is_random_access_iterator(_Iter) noexcept { return true; }

#endif // __ge_cxx20

} // namespace cxx::iterator

#endif // __CPLUSPLUS_ITERATOR__CONCEPT_H
