#pragma once

#ifndef __CPLUSPLUS_OOP_INITIALIZE_LIST_H
#define __CPLUSPLUS_OOP_INITIALIZE_LIST_H

#include <memory>
#include <utility>

namespace cpp::oop {
	/// @brief 定义表示序列的类
	template <typename T, typename _Alloc = std::allocator<T>>
	class Sequence final {
	private:
		T* _data;
		size_t _size;

		_Alloc __alloc;

		T* __allocate_me(size_t size) {
			_data = __alloc.allocate(size);
			_size = size;

			return _data;
		}

		template <typename _Iter>
		void __from_iter(_Iter begin, _Iter end) {
			std::uninitialized_copy(begin, end, __allocate_me(std::distance(begin, end)));
		}

		void __copy(T* data, size_t size) {
			_data = __alloc.allocate(_size);

			_data = std::uninitialized_copy(data, data + size, __alloc.allocate(size));
			_size = size;
		}

		void __free() {
			if (_data) {
				T* data = std::exchange(_data, nullptr);
				size_t size = std::exchange(_size, 0);

				std::destroy_n(data, size);
				__alloc.deallocate(data, size);
			}
		}
	public:
		Sequence() : _data(nullptr), _size(0) {}

		Sequence(std::initializer_list<T> _list) { __from_iter(_list.begin(), _list.end()); }

		Sequence(const Sequence& o) { __copy(o._data, o._size); }

		~Sequence() {
			__alloc.deallocate(_data, size());
		}
	};
} // ! namespace cpp::oop

#endif // ! __CPLUSPLUS_OOP_INHERIT_H
