#pragma once

#ifndef __CPLUSPLUS_OOP_AFFINE_PTR_H
#define __CPLUSPLUS_OOP_AFFINE_PTR_H

#include <memory>
#include <type_traits>

namespace cpp {
	using namespace std;

	template<typename _Iter>
	struct _IterToolkit {
		using opt_sub_t = decltype(_Iter::operator-);
	};

	/// @brief 定义仿指针类型
	///
	/// 所谓的 "仿指针", 即一个重载了 `*` (解引) 运算符的类型
	///
	/// 同理, 重载了 `[]` 运算符的类型, 可以看作是 "仿数组"
	///
	/// @tparam T
	template<typename T, typename _Alloc = allocator<T>>
	class Box {
	private:
		_Alloc _alloc;

		T* _ptr;
		size_t _len;
	private:
		/// @brief 根据所给值创建指向单个对象的指针
		///
		/// @param val 所给值
		void _from_value(const T& val, size_t len) {
			// 分配内存
			T* ptr = _alloc.allocate(len);

			// 为内存的每个元素调用 `T` 类型的构造函数
			for (size_t i = 0; i < len; ++i) {
				new (ptr + i) T(val);
			}

			_ptr = ptr;
			_len = len;
		}

		/// @brief 销毁当前指针
		void _delete() {
			T* ptr = _ptr;

			if (ptr) {
				_ptr = nullptr;

				size_t len = _len;
				_len = 0;

				// 为数组各元素调用析构函数
				for (size_t i = 0; i < len; ++i) {
					(ptr + i)->~T();
				}

				// 释放数组内存
				_alloc.deallocate(ptr, len);
			}
		}
	public:
		/// @brief 默认构造函数
		Box() :
			_ptr(nullptr),
			_len(0) {}

		/// @brief 参数构造器
		///
		/// 根据所给的值创建一个堆上的指针, 并存储该值
		///
		/// @param value 所给的值
		/// @param len 元素个数
		Box(const T& value, size_t len = 1) {
			_from_value(value, len);
		}

		/// @brief 参数构造器
		///
		/// 根据从另一个 `Box` 对象分离的指针构造当前对象
		///
		/// @param ptr 从另一个对象中分离的指针
		/// @param len 指针指向的元素个数
		Box(T* ptr, size_t len = 1) :
			Box() {
			attach(ptr, len);
		}

		/// @brief 禁用拷贝构造函数
		Box(const Box& o) = delete;

		/// @brief 析构函数, 销毁当前堆内存
		virtual ~Box() {
			_delete();
		}

		/// @brief 禁用赋值运算符
		Box& operator=(const Box& o) = delete;

		/// @brief 重载 `*` (解引) 运算符, 获取当前指针指向的的值的可变引用
		///
		/// @return 当前指针指向值的可变引用
		T& operator*() { return *_ptr; }

		/// @brief 重载 `*` (解引) 运算符, 获取当前指针指向的的值的只读引用
		///
		/// @return 当前指针指向值的只读引用
		const T& operator*() const { return *_ptr; }

		/// @brief 重载 `[]` 运算符 (通过下标取值)
		///
		/// @param n 下标值
		/// @return 下标对应的值的可变引用
		T& operator[](size_t n) { return *(_ptr + n); }

		/// @brief 重载 `[]` 运算符 (通过下标取值)
		///
		/// @param n 下标值
		/// @return 下标对应的值的只读引用
		const T& operator[](size_t n) const { return *(_ptr + n); }

		/// @brief 获取当前指针指向的元素个数
		///
		/// @return 当前指针指向的元素个数
		size_t size() const { return _len; }

		/// @brief 分离当前指针
		///
		/// @return 当前指针
		T* detach() {
			T* ptr = _ptr;

			_ptr = nullptr;
			_len = 0;

			return ptr;
		}

		/// @brief 根据从另一个 `Box` 对象分离的指针构造当前对象
		///
		/// @param ptr 从另一个对象中分离的指针
		/// @param len 指针指向的元素个数
		void attach(T* ptr, size_t len = 1) {
			_delete();

			_ptr = ptr;
			_len = len;
		}

		/// @brief 根据所给的迭代器创建指向数组的指针
		///
		/// @tparam _Iter
		/// @param begin 起始位置迭代器
		/// @param end 结束位置迭代器
		template<typename _Iter>
		static Box from_iter(const _Iter& begin, const _Iter& end) {
			// 计算数组长度
			size_t len = end - begin;

			// 分配内存
			T* ptr = (_Alloc()).allocate(len);

			// 为内存的每个元素调用 `T` 类型的构造函数
			for (size_t i = 0; i < len; ++i) {
				new (ptr + i) T(*(begin + i));
			}

			return Box(ptr, len);
		}
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_OOP_AFFINE_PTR_H
