#pragma once

#ifndef __CPLUSPLUS_ITERATOR__DYNAMIC_ARRAY_H
#define __CPLUSPLUS_ITERATOR__DYNAMIC_ARRAY_H

#include "iterator.h"

namespace cxx::iterator {

	/// @brief 定义动态数组类型, 可以按需调整数组长度
	///
	/// @tparam T 数组元素类型
	template <typename T, typename _Alloc = std::allocator<T>>
	class dynamic_array {
		using __self = dynamic_array<T>;
	public:
		using iterator = ptr_based_iterator<T>;
		using reverse_iterator = ptr_based_reverse_iterator<T>;
		using const_iterator = ptr_based_iterator<const T>;
		using const_reverse_iterator = ptr_based_reverse_iterator<const T>;
		using allocator_type = _Alloc;

		/// @brief 默认构造器
		dynamic_array() : _data(nullptr), _size(0) { }

		/// @brief 初始化数组
		///
		/// @param size 数据长度
		dynamic_array(size_t size, const T& val = T()) {
			std::uninitialized_fill_n(__alloc_n(size), size, val);
		}

		/// @brief 参数构造器
		///
		/// @param data 数据指针
		/// @param size 数据长度
		dynamic_array(const T* data, size_t size) {
			std::uninitialized_copy_n(data, size, __alloc_n(size));
		}

		/// @brief 参数构造器
		///
		/// @param init_list 初始化列表对象
		dynamic_array(std::initializer_list<T> init_list) {
			std::uninitialized_copy_n(init_list.begin(), init_list.size(), __alloc_n(init_list.size()));
		}

		/// @brief 参数构造器
		///
		/// @param arr `array` 数组对象
		template <size_t N>
		dynamic_array(const std::array<T, N>& arr) {
			std::uninitialized_copy_n(arr.begin(), N, __alloc_n(N));
		}

		/// @brief 参数构造器
		///
		/// @tparam N 数组长度
		/// @param arr 原生数组对象
		template <size_t N>
		dynamic_array(const T arr[N]) {
			std::uninitialized_copy_n(arr, N, __alloc_n(N));
		}

		/// @brief 拷贝构造器
		///
		/// @param o 另一个对象
		dynamic_array(const __self& o) {
			std::uninitialized_copy_n(o._data, o._size, __alloc_n(o._size));
		}

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		dynamic_array(__self&& o) noexcept { __move(std::forward(o)); }

		/// @brief 析构函数
		virtual ~dynamic_array() { __free(); }

		/// @brief 赋值运算符重载
		///
		/// @param o 其它对象引用
		/// @return 当前对象引用
		__self& operator=(const __self& o) {
			if (this != &o) {
				__free();
				std::uninitialized_copy_n(o._data, o._size, __alloc_n(o._size));
			}
			return *this;
		}

		/// @brief 移动赋值运算符重载
		///
		/// @param o 其它对象右值引用
		/// @return 当前对象引用
		__self& operator=(__self&& o) noexcept {
			if (this != &o) {
				__free();
				__move(std::forward(o));
			}
			return *this;
		}

		/// @brief 获取当前数据指针
		///
		/// @return 数据指针
		T* data() { return _data; }
		const T* data() const { return _data; }

		/// @brief 获取起始迭代器对象
		///
		/// @return 迭代器对象
		iterator begin() { return iterator(_data); }

		/// @brief 获取起始只读迭代器
		///
		/// @return 只读迭代器对象
		const_iterator begin() const { return const_iterator(_data); }

		/// @brief 获取终止迭代器对象
		///
		/// @return 迭代器对象
		iterator end() { return iterator(_data + _size); }

		/// @brief 获取终止只读迭代器对象
		///
		/// @return 只读迭代器对象
		const_iterator end() const { return const_iterator(_data + _size); }

		/// @brief 获取起始反向迭代器对象
		///
		/// @return 迭代器对象
		reverse_iterator rbegin() { return reverse_iterator(_data + _size - 1); }

		/// @brief 获取起始只读反向迭代器对象
		///
		/// @return 只读迭代器对象
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_data + _size - 1); }

		/// @brief 获取起始终止迭代器对象
		///
		/// @return 迭代器对象
		reverse_iterator rend() { return reverse_iterator(_data - 1); }

		/// @brief 获取起始终止迭代器对象
		///
		/// @return 迭代器对象
		const_reverse_iterator rend() const { return const_reverse_iterator(_data - 1); }

	private:
		T* _data;
		size_t _size;

		allocator_type _alloc;

		/// @brief 分配地址
		///
		/// @param size 要分配的地址大小
		/// @return
		T* __alloc_n(size_t size) {
			_data = size ? _alloc.allocate(size) : nullptr;
			_size = size;
			return _data;
		}

		/// @brief 将另一个对象进行移动
		///
		/// @param o 另一个对象的右值引用
		void __move(__self&& o) noexcept {
#if __ge_cxx17
			if (_size = std::exchange(o._size, 0); _size > 0) {
#else
			_size = std::exchange(o._size, 0);
			if (_size > 0) {
#endif
				_data = std::exchange(o._data, nullptr);
			}
		}

		/// @brief 销毁当前数据指针
		void __free() {
#if __ge_cxx17
			if (T* data = std::exchange(_data, nullptr); data) {
#else
			T* data = std::exchange(_data, nullptr);
			if (data) {
#endif
				_alloc.deallocate(data, _size);
				_data = nullptr;
				_size = 0;
			}
		}
	};

} // namespace cxx::iterator

#endif // __CPLUSPLUS_ITERATOR__DYNAMIC_ARRAY_H
