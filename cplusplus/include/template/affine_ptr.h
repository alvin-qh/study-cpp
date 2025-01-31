#pragma once

#ifndef __CPLUSPLUS_TEMPLATE__AFFINE_PTR_H
#define __CPLUSPLUS_TEMPLATE__AFFINE_PTR_H

#include <utility>
#include <memory>

namespace cxx::templated {
	using namespace std;

	/// @brief 定义仿指针类型
	///
	/// 所谓的 "仿指针", 即一个重载了 `*` (解引) 运算符的类型
	///
	/// 同理, 重载了 `[]` 运算符的类型, 可以看作是 "仿数组"
	///
	/// @tparam T
	template<typename T, typename _Alloc = allocator<T>>
	class Box {
		typedef Box<T, _Alloc> Self;

	public:
		/// @brief 默认构造函数
		Box() : Box(nullptr, 0) { }

		/// @brief 参数构造器
		///
		/// 根据所给的值创建一个堆上的指针, 并存储该值
		///
		/// @param value 所给的值
		/// @param len 元素个数
		Box(const T& value, size_t len = 1) { _allocate(value, len); }

		/// @brief 参数构造器
		///
		/// 根据从另一个 `Box` 对象分离的指针构造当前对象
		///
		/// @param ptr 从另一个对象中分离的指针
		/// @param len 指针指向的元素个数
		Box(T* ptr, size_t len = 1) : _ptr(ptr), _len(len) { }

		/// @brief 禁用拷贝构造函数
		Box(const Self&) = delete;

		/// @brief 移动构造器
		///
		/// @param o 被移动对象
		Box(Self&& o) noexcept :
			_ptr(std::exchange(o._ptr, nullptr)),
			_len(std::exchange(o._len, 0)) { }

		/// @brief 析构函数, 销毁当前堆内存
		virtual ~Box() { _free(); }

		/// @brief 禁用赋值运算符
		Self& operator=(const Self&) = delete;

		/// @brief 重载移动赋值运算符
		///
		/// @param o 被移动对象
		/// @return 当前对象引用
		Self& operator=(Self&& o) noexcept {
#if __ge_cxx17
			if (T* ptr = std::exchange(_ptr, nullptr); ptr != nullptr) {
#else
			T* ptr = std::exchange(_ptr, nullptr);
			if (ptr) {
#endif
				_alloc.deallocate(ptr, _len);
			}

			_ptr = std::exchange(o._ptr, nullptr);
			_len = std::exchange(o._len, 0);
			return *this;
			};

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

		/// @brief 重载布尔运算符, 确定指针有效
		///
		/// @return 指针是否有效
		operator bool() const { return _ptr != nullptr; }

		/// @brief 获取当前指针指向的元素个数
		///
		/// @return 当前指针指向的元素个数
		size_t size() const { return _len; }

		/// @brief 根据从另一个 `Box` 对象分离的指针构造当前对象
		///
		/// @param ptr 从另一个对象中分离的指针
		/// @param len 指针指向的元素个数
		void attach(T * ptr, size_t len = 1) {
			_free();

			_ptr = ptr;
			_len = len;
		}

		/// @brief 根据所给的迭代器创建指向数组的指针
		///
		/// @tparam _Iter
		/// @param begin 起始位置迭代器
		/// @param end 结束位置迭代器
		template<typename _Iter>
		static Self from_iter(const _Iter & begin, const _Iter & end) {
			// 计算数组长度
			size_t len = std::distance(begin, end);

			// 分配内存并拷贝数据
			T* ptr = (_Alloc()).allocate(len);
			std::uninitialized_copy(begin, end, ptr);

			return Box(ptr, len);
		}

	private:
		T* _ptr;
		size_t _len;

		_Alloc _alloc;

		/// @brief 根据所给值创建指向单个对象的指针
		///
		/// @param val 所给值
		void _allocate(const T & val, size_t len) {
			// 分配内存, 为内存的每个元素调用 `T` 类型的构造函数
			_ptr = _alloc.allocate(len);
			std::uninitialized_fill_n(_ptr, len, val);
			_len = len;
		}

		/// @brief 销毁当前指针
		void _free() {
			// 为数组各元素调用析构函数, 释放数组内存
#if __ge_cxx17
			if (T* ptr = std::exchange(_ptr, nullptr); ptr) {
				std::destroy_n(ptr, _len);
#else
			T* ptr = std::exchange(_ptr, nullptr);
			if (ptr) {
				for (size_t i = 0; i < _len; ++i) {
					ptr[i].~T();
				}
#endif
				_alloc.deallocate(ptr, _len);
				_len = 0;
			}
			}
		};

		} // namespace cxx::templated

#endif // __CPLUSPLUS_TEMPLATE_AFFINE_PTR_H
