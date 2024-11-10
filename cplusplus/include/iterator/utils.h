#pragma once

#ifndef __CPLUSPLUS_ITERATOR__UTILS_H
#define __CPLUSPLUS_ITERATOR__UTILS_H

#include <iterator>

namespace cxx::iterator {

	/// @brief 比较两组迭代器内容是否相同
	///
	/// @tparam _Iter1 第一组迭代器类型
	/// @tparam _Iter2 第二组迭代器类型
	/// @param begin1 第一组迭代器起始对象
	/// @param end1 第一组迭代器终止对象
	/// @param begin2 第二组迭代器起始对象
	/// @param end2 第二组迭代器终止对象
	/// @return 出现差异的位置 (从 1 开始)
	template<typename _Iter1, typename _Iter2>
#if __ge_cxx20
		requires std::input_iterator<_Iter1>&& std::input_iterator<_Iter2>
#endif
	ptrdiff_t compare_iterators(_Iter1 begin1, _Iter1 end1, _Iter2 begin2, _Iter2 end2) noexcept {
		ptrdiff_t diff = 0;

		auto it1 = begin1;
		auto it2 = begin2;

		for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
			++diff;
			if (*it1 != *it2) {
				break;
			}
		}

		if (it1 == end1 && it2 == end2) {
			return 0;
		}
		return diff;
	}

} // namespace cxx::iterator

#endif // __CPLUSPLUS_ITERATOR_UTILS_H
