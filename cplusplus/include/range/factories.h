#pragma once

#ifndef __CPLUSPLUS_RANGE__FACTORIES_H
#define __CPLUSPLUS_RANGE__FACTORIES_H

#if __ge_cxx20

#include <iterator>

namespace cxx::range {
	using namespace std;

	template <typename _Iter>
	concept __integral_iterator = forward_iterator<_Iter> && std::is_integral<typename _Iter::value_type>::value;

	/// @brief 定义一个视图, 只包含奇数值
	/// @tparam _N
	/// @tparam _C
	template <typename _Iter>
		requires __integral_iterator<_Iter>
	class odd_number_view : public ranges::view_interface<odd_number_view<_Iter>> {
	public:
		struct __iterator {
		private:
			_Iter _iter, _end;
		public:
			using iterator_concept = forward_iterator_tag;
			using difference_type = ptrdiff_t;
			using value_type = typename _Iter::value_type;
			using const_value_type = const typename _Iter::value_type;

			__iterator() = default;
			__iterator(const _Iter& iter, const _Iter& end) : _iter(iter), _end(end) {}
			__iterator(const __iterator&) = default;
			__iterator(__iterator&&) = default;

			__iterator& operator++() {
				while (_iter != _end) {
					++_iter;
					if (_iter == _end || *_iter % 2 != 0) {
						break;
					}
				}
				return *this;
			}

			__iterator operator++(int) const {
				auto iter = *this;
				++*this;
				return iter;
			}

			value_type& operator*() { return *_iter; }
			const_value_type& operator*() const { return *_iter; }

			bool operator==(const __iterator& o) const { return _iter == o._iter; }

			__iterator& operator=(const __iterator&) = default;
		};

	private:
		_Iter _begin, _end;
	public:
		odd_number_view() = default;
		odd_number_view(const _Iter& begin, const _Iter& end) : _begin(begin), _end(end) {}

		__iterator begin() const { return __iterator(_begin, _end); }
		__iterator end() const { return __iterator(_end, _end); }
	};

	template <typename _N>
		requires is_integral<_N>::value
	odd_number_view<typename vector<_N>::const_iterator> odd_number(const vector<_N>& vec) {
		return odd_number_view<typename vector<_N>::const_iterator>(vec.begin(), vec.end());
	}

} // namespace cxx::range

#endif // __ge_cxx20

#endif // !__CPLUSPLUS_RANGE__FACTORIES_H
