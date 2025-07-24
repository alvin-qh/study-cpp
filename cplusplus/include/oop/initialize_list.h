#pragma once

#ifndef __CPLUSPLUS_OOP__INITIALIZE_LIST_H
#define __CPLUSPLUS_OOP__INITIALIZE_LIST_H

#include <memory>
#include <utility>

#include "iterator/iterator.h"

namespace cxx::oop {
	using namespace cxx::iterator;

	/// @brief 定义集合类用于展示初始化列表的使用
	///
	/// 将 `std::initializer_list` 类型对象作为构造器唯一参数, 即可通过
	/// "brace-enclosed initializer list" 语法进行对象初始化
	template <typename T, typename _Alloc = std::allocator<T>>
	class Sequence final {
	public:
		using iterator = ptr_based_iterator<T>;
		using const_iterator = ptr_based_iterator<const T>;
		using reverse_iterator = ptr_based_reverse_iterator<T>;
		using const_reverse_iterator = ptr_based_reverse_iterator<const T>;

		/// @brief 默认构造器
		Sequence() : _data(nullptr), _size(0) { }

		/// @brief 参数构造器
		///
		/// @param size 数组长度
		/// @param init_val 数组元素初始值
		Sequence(size_t size, const T& init_val = T()) {
			std::uninitialized_fill_n(__allocate_me(size), size, init_val);
		}

		/// @brief 通过 "brace-enclosed initializer list" 构造对象
		///
		/// @param _list "brace-enclosed initializer list" 产生的参数列表集合
		Sequence(std::initializer_list<T> _list) {
			std::uninitialized_copy(_list.begin(), _list.end(), __allocate_me(_list.size()));
		}

		/// @brief 拷贝构造器
		///
		/// @param o 其它对象引用
		Sequence(const Sequence& o) { __copy(o._data, o._size); }

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		Sequence(Sequence&& o) { __move(o); }

		/// @brief 析构函数
		~Sequence() { __alloc.deallocate(_data, size()); }

		/// @brief 赋值运算符重载
		///
		/// @param o 其它对象引用
		/// @return 当前对象引用
		const Sequence& operator=(const Sequence& o) {
			if (this != &o) {
				__free();
				__copy(o._data, o._size);
			}
			return *this;
		}

		/// @brief 移动复制运算符重载
		///
		/// @param o 其它对象右值引用
		/// @return 当前对象引用
		Sequence& operator=(Sequence&& o) {
			if (this != &o) {
				__free();
				__move(o);
			}
			return *this;
		}

		/// @brief 索引运算符重载, 获取指定下标的数组元素引用
		///
		/// @param n 下标值
		/// @return 指定下标对应的元素引用
		T& operator[](size_t n) { return _data[n]; }

		/// @brief 索引运算符重载, 获取指定下标的数组元素只读引用
		///
		/// @param n 下标值
		/// @return 指定下标对应的元素只读引用
		const T& operator[](size_t n) const { return _data[n]; }

		/// @brief 获取数组长度
		///
		/// @return 数组长度
		size_t size() const { return _size; }

		/// @brief 获取正向起始迭代器
		///
		/// @return 迭代器对象
		iterator begin() { return iterator(_data); }

		/// @brief 获取正向起始只读迭代器
		///
		/// @return 只读迭代器对象
		const_iterator begin() const { return const_iterator(_data); }

		/// @brief 获取正向终止迭代器
		///
		/// @return 迭代器对象
		iterator end() { return iterator(_data + _size); }

		/// @brief 获取正向终止只读迭代器
		///
		/// @return 只读迭代器对象
		const_iterator end() const { return const_iterator(_data + _size); }

		/// @brief 返回指向数据地址的指针
		///
		/// @return 数据指针
		T* data() { return _data; }

		/// @brief 返回指向数据地址的只读指针
		///
		/// @return 数据只读指针
		const T* data() const { return _data; }

	private:
		T* _data;
		size_t _size;

		_Alloc __alloc;

		/// @brief 按所需数组长度分配内存
		///
		/// @param size 数组长度
		/// @return 分配内存地址的指针
		T* __allocate_me(size_t size) {
			_data = __alloc.allocate(size);
			_size = size;
			return _data;
		}

		/// @brief 在内存中复制数据
		///
		/// @param data 数据指针
		/// @param size 数组长度
		void __copy(T* data, size_t size) {
			std::vector<int>::iterator
				_data = __alloc.allocate(_size);
			std::uninitialized_copy(data, data + size, __alloc.allocate(size));
			_size = size;
		}

		/// @brief 将另一个对象的内容移动到当前对象
		///
		/// @param o 另一个对象引用
		void __move(Sequence& o) noexcept {
			_data = std::exchange(o._data, nullptr);
			_size = std::exchange(o._size, 0);
		}

		/// @brief 销毁当前指针内存
		void __free() {
			if (_data) {
				T* data = std::exchange(_data, nullptr);
				size_t size = std::exchange(_size, 0);

#if __ge_cxx17
				std::destroy_n(data, size);
#else
				for (size_t i = 0; i < size; ++i) {
					data[i].~T();
				}
#endif
				__alloc.deallocate(data, size);
			}
		}
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OOP__INITIALIZE_LIST_H
