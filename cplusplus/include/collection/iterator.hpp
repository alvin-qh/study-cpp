#pragma once

#ifndef __CPLUSPLUS_COLLECTION_ITERATOR_H
#define __CPLUSPLUS_COLLECTION_ITERATOR_H

#include <type_traits>

namespace cpp::collection {

#if (__cplusplus >= 201703L)

	/// @brief 通过 `concept` 关键字声明符合特定要求的模板定义
	template<typename T>
	concept number_only_type = std::is_arithmetic<T>::value;

	template <number_only_type>
	class range_iterator;

	template <number_only_type>
	class range_reverse_iterator;

	template <number_only_type T>
	class range {
		typedef range_iterator<T> iterator_type;
		typedef range_reverse_iterator<T> reverse_iterator_type;
		typedef range<T> __self_type;
	private:
		T _from, _to;
	public:
		range(T from, T to) : _from(from), _to(to) {}

		range(const __self_type&) = default;

		~range() = default;

		__self_type& operator=(const __self_type&) = default;

		const T& from() const { return _from; }

		const T& to() const { return _to; }

		iterator_type begin() { return iterator_type(_from); }

		iterator_type end() { return iterator_type(_to); }

		reverse_iterator_type rbegin() { return reverse_iterator_type(_to); }

		reverse_iterator_type rend() { return reverse_iterator_type(_from); }
	};

	template <number_only_type T>
	class range_iterator {
		template <number_only_type> friend class range;

		typedef range_iterator<T> __self_type;
	protected:
		T _value;

		explicit range_iterator(const T& value) : _value(value) {}
	public:
		range_iterator(const __self_type&) = default;

		__self_type& operator=(const __self_type&) = default;

		__self_type& operator++() {
			++_value;
			return *this;
		}

		__self_type operator++(int) {
			__self_type tmp(*this);
			++_value;
			return tmp;
		}

		__self_type operator+(const T& n) const {
			__self_type tmp(*this);
			tmp._value += n;
			return tmp;
		}

		__self_type operator-(const T& n) const {
			__self_type tmp(*this);
			tmp._value -= n;
			return tmp;
		}

		__self_type& operator+=(const T& n) {
			_value += n;
			return *this;
		}

		__self_type& operator-=(const T& n) {
			_value -= n;
			return *this;
		}

		const T& operator*() const { return _value; }

		T& operator*() { return _value; }

		bool operator==(const __self_type& o) const { return _value == o._value; }

		bool operator!=(const __self_type& o) const { return !(*this == o); }

		bool operator>(const __self_type& o) const { return _value > o._value; }

		bool operator<(const __self_type& o) const { return _value < o._value; }

		bool operator>=(const __self_type& o) const { return _value >= o._value; }

		bool operator<=(const __self_type& o) const { return _value <= o._value; }
	};

	template <number_only_type T>
	class range_reverse_iterator : public range_iterator<T> {
		template <number_only_type> friend class range;

		typedef range_iterator<T> __base_type;
		typedef range_reverse_iterator<T> __self_type;
	protected:
		explicit range_reverse_iterator(const T& value) : __base_type(value) { --__base_type::_value; }
	public:
		range_reverse_iterator(const __self_type& o) : __base_type(o) {}

		__self_type& operator=(const __self_type& o) {
			__base_type::operator=(o);
			return *this;
		}

		__self_type& operator++() {
			--__base_type::_value;
			return *this;
		}

		__self_type operator++(int) {
			__self_type tmp(*this);
			--__base_type::_value;
			return tmp;
		}
	};

#else

	template <typename T>
	class Range {
	};

#endif // _cplusplus < 201703L

		} // namespace cpp::collection

#endif
