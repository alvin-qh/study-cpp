/// `unique_ptr`
///
/// `unique_ptr` 不共享它的指针, 即:
/// - `unique_ptr` 对象无法在变量之间赋值;
/// - `unique_ptr` 无法通过值传递到函数;
///
/// 只能通过移动语义, 对 `unique_ptr` 对象进行移动操作, 这意味着内存资源所有权将转移到另一个 `unique_ptr` 变量, 则原始 `unique_ptr`
/// 不再拥有此资源; 当构造 `unique_ptr` 时, 可使用 `make_unique` 工具函数来创建 `unique_ptr` 对象实例;

/// `shared_ptr`
///
/// `shared_ptr` 专为多个所有者需要管理对象生命周期的方案而设计, 当在变量间传递同一个 `shared_ptr` 实例时, 所有变量均指向同一个资源,
/// 通过引用计数器的加减来管理资源最终的生命周期, 可使用 `make_shared` 工具函数来创建 `shared_ptr` 对象实例;

#pragma once

#ifndef __CPLUSPLUS_PTR__SHARED_PTR_H
#define __CPLUSPLUS_PTR__SHARED_PTR_H

#include <cstdint>
#include <memory>
#include <initializer_list>
#include <stdexcept>

namespace cxx::pointer {

	/// @brief 用于测试智能指针的类
	///
	/// 该类型表示一个非常大的数组数据, 通过 `T` 表示数组元素类型, `SIZE` 表示数组大小
	///
	/// 一般情况下, 不应该将过大的数据结构放在栈内存中, 而是通过 `new` 等运算符在堆内存中分配空间
	///
	/// @tparam T 数组元素类型
	/// @tparam SIZE 数组大小
	template<typename T, size_t SIZE>
	class LargeObject {
	public:
		/// @brief 默认构造器
		LargeObject() : LargeObject(T()) { }

		/// @brief 参数构造器
		///
		/// @param init_val 初始值, 数组的每一项都会初始化为该值
		LargeObject(const T& init_val) {
			std::uninitialized_fill_n(_data, SIZE, init_val);
		};

		/// @brief 参数构造器
		///
		/// @param l 数据列表
		LargeObject(std::initializer_list<T> l) { _fill(l.begin(), l.end()); }

		/// @brief 拷贝构造器
		///
		/// @param o 另一个对象
		LargeObject(const LargeObject& o) { std::copy(o._data, o._data + SIZE, _data); }

		/// @brief 析构函数
		virtual ~LargeObject() {
#if __ge_cxx17
			std::destroy_n(_data, SIZE);
#else
			for (size_t i = 0; i < SIZE; ++i) {
				_data[i].~T();
			}
#endif
		}

		/// @brief 赋值构造器
		///
		/// @param o 另一个对象引用
		/// @return 当前对象引用
		LargeObject& operator=(const LargeObject& o) {
			if (this != &o) {
				std::copy(o._data, o._data + SIZE, _data);
			}
			return *this;
		};

		/// @brief 重载下标操作符, 获取数组的每一项元素的引用
		///
		/// @param index 下标值
		/// @return 下标对应的元素引用
		T& operator[](size_t index) {
			if (index >= SIZE) {
				throw std::out_of_range("index out of range");
			}
			return _data[index];
		}

		/// @brief 重载下标操作符, 获取数组的每一项元素的只读引用
		///
		/// @param index 下标值
		/// @return 下标对应的元素只读引用
		const T& operator[](size_t index) const {
			return const_cast<LargeObject*>(this)->operator[](index);
		}

		/// @brief 获取数组长度
		///
		/// @return 数组长度
		constexpr size_t size() const { return SIZE; }

	private:
		// 保存数据的数组
		T _data[SIZE];

		/// @brief 向数组填充数据
		///
		/// @tparam _Iter 原数据的迭代器类型
		/// @param begin 原数据的起始迭代器实例
		/// @param end 原数据的结束迭代器实例
		template <typename _Iter>
		void _fill(_Iter begin, _Iter end) {
			size_t i = 0;
			for (_Iter it = begin; it != end; ++it) {
				_data[i++] = *it;
			}
		}
	};

} // namespace cxx::pointer

#endif // __CPLUSPLUS_PTR__SHARED_PTR_H
