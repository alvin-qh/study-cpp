#pragma once

#ifndef __CPLUSPLUS_OOP_AFFINE_PTR_H
#define __CPLUSPLUS_OOP_AFFINE_PTR_H

#include <memory>

using namespace std;

namespace cpp {
	/// @brief 定义仿指针类型
	///
	/// 所谓的仿指针, 即一个重载了 `*` (解引) 运算符的类型
	///
	/// @tparam T
	template<typename T, typename _Alloc = allocator<T>>
	class Box {
	private:
		T* _ptr;
		size_t _len;
		_Alloc _alloc;

	private:
		void _new_one(const T& val) {
			_new_n(&val, &val + 1);
		}

		template<typename _Iter>
		void _new_n(const _Iter& begin, const _Iter& end) {
			size_t n = end - begin;

			T* ptr = _alloc.allocate(n);
			for (size_t i = 0; i < n; ++i) {
				new (ptr + i) T(*(begin + i));
			}
			_ptr = ptr;
			_len = n;
		}

		void _delete() {
			auto* ptr = _ptr;
			if (_ptr) {
				for (size_t i = 0; i < _len; ++i) {
					(ptr + i)->~T();
				}
				_alloc.deallocate(ptr, _len);
				_ptr = nullptr;
				_len = 0;
			}
		}

	public:
		Box()
			: _ptr(nullptr) {}

		Box(const T& value) {
			_new_one(value);
		}

		Box(const Box& o) = delete;

		virtual ~Box() {
		}

		Box& operator=(const Box& o) = delete;

		T& operator*() { return *_ptr; }

		const T& operator*() const { return *_ptr; }

		T* detach() {
			T* ptr = _ptr;
			_ptr = nullptr;
			return ptr;
		}
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_OOP_AFFINE_PTR_H
