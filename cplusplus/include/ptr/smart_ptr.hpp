#pragma once

#ifndef __CPLUSPLUS_OOP_AFFINE_SMART_PTR_H
#define __CPLUSPLUS_OOP_AFFINE_SMART_PTR_H

#include <cstdint>
#include <memory>
#include <initializer_list>
#include <stdexcept>

namespace cpp::ptr {
	template<typename T, size_t SIZE>
	class LargeObject {
	private:
		T data[SIZE];

		template <typename _Iter>
		void _fill(_Iter begin, _Iter end) {
			size_t i = 0;
			for (_Iter it = begin; it != end; ++it) {
				data[i++] = *it;
			}
		}
	public:
		LargeObject() : LargeObject(T()) {}

		LargeObject(const T& init_val) {
			for (size_t i = 0; i < SIZE; ++i) {
				new (data + i) T(init_val);
			}
		};

		LargeObject(std::initializer_list<T> l) { _fill(l.begin(), l.end()); }

		/// @brief 禁用拷贝构造器
		LargeObject(const LargeObject&) = delete;

		virtual ~LargeObject() {
			for (size_t i = 0; i < SIZE; ++i) {
				data[i].~T();
			}
		}

		/// @brief 禁用赋值运算
		LargeObject& operator=(const LargeObject&) = delete;

		T& operator[](size_t index) {
			if (index >= SIZE) {
				throw std::out_of_range("index out of range");
			}
			return data[index];
		}

		const T& operator[](size_t index) const {
			return const_cast<LargeObject*>(this)->operator[](index);
		}

		constexpr size_t size() const { return SIZE; }
	};
}

#endif // !__CPLUSPLUS_OOP_AFFINE_SMART_PTR_H
