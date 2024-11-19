#pragma once

#ifndef __CPLUSPLUS_RANGE__FACTORIES_H
#define __CPLUSPLUS_RANGE__FACTORIES_H

#if __ge_cxx20

#include <iterator>

namespace cxx::range {
	using namespace std;

	template <typename _Iter>
	concept __integral_iterator = input_iterator<_Iter> && std::is_integral<typename _Iter::value_type>::value;

	/// @brief 定义一个视图, 只包含奇数值
	/// @tparam _N
	/// @tparam _C
	template <typename _Iter>
		requires __integral_iterator<_Iter>
	class odd_number_view : public ranges::view_interface<odd_number_view<_Iter>> {
	public:
		using value_type = typename _Iter::value_type;
	private:
		struct __iterator {
			_Iter _iter, _end;

			__iterator() = default;

			__iterator(const _Iter& iter, const _Iter& end) :
				_iter(iter), _end(end) {
			}

			const value_type& operator*() const { return *_iter; }

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

			bool operator==(const __iterator& o) const { return _iter == o._iter; }
		};

		__iterator _begin, _end;
	public:
		odd_number_view() = default;

		odd_number_view(const _Iter& begin, const _Iter& end) :
			_begin(begin, end), _end(end, end) {
		}

		__iterator begin() const { return _begin; }

		__iterator end() const { return _end; }
	};

	template <typename _N>
		requires is_integral<_N>::value
	odd_number_view<typename vector<_N>::const_iterator> odd_number(const vector<_N>& vec) {
		return odd_number_view<typename vector<_N>::const_iterator>(vec.begin(), vec.end());
	}

} // namespace cxx::range

#endif // __ge_cxx20

#endif // !__CPLUSPLUS_RANGE__FACTORIES_H
