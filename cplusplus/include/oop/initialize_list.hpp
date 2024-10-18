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

		void __copy(T* data, size_t size) {
			_data = __alloc.allocate(_size);
			std::uninitialized_copy(data, data + size, __alloc.allocate(size));
			_size = size;
		}

		void __move(Sequence& o) noexcept {
			_data = std::exchange(o._data, nullptr);
			_size = std::exchange(o._size, 0);
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

		Sequence(size_t size, const T& init_val = T()) {
			std::uninitialized_fill_n(__allocate_me(size), size, init_val);
		}

		Sequence(std::initializer_list<T> _list) {
			std::uninitialized_copy(_list.begin(), _list.end(), __allocate_me(_list.size()));
		}

		Sequence(const Sequence& o) { __copy(o._data, o._size); }

		Sequence(Sequence&& o) { __move(o); }

		~Sequence() { __alloc.deallocate(_data, size()); }

		const Sequence& operator=(const Sequence& o) {
			if (this != &o) {
				__free();
				__copy(o._data, o._size);
			}
			return *this;
		}

		Sequence& operator=(Sequence&& o) {
			if (this != &o) {
				__free();
				__move(o);
			}
			return *this;
		}

		T& operator[](size_t n) { return _data[n]; }

		const T& operator[](size_t n) const { return _data[n]; }

		size_t size() const { return _size; }

		T* begin() { return _data; }

		const T* begin() const { return _data; }

		T* end() { return _data + _size; }

		const T* end() const { return _data + _size; }

		T* data() { return _data; }

		const T* data() const { return _data; }
	};
} // ! namespace cpp::oop

#endif // ! __CPLUSPLUS_OOP_INHERIT_H
