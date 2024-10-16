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
		T _data[SIZE];

		template <typename _Iter>
		void _fill(_Iter begin, _Iter end) {
			size_t i = 0;
			for (_Iter it = begin; it != end; ++it) {
				_data[i++] = *it;
			}
		}
	public:
		LargeObject() : LargeObject(T()) {}

		LargeObject(const T& init_val) {
			for (size_t i = 0; i < SIZE; ++i) {
				new (_data + i) T(init_val);
			}
		};

		LargeObject(std::initializer_list<T> l) { _fill(l.begin(), l.end()); }

		/// @brief 禁用拷贝构造器
		LargeObject(const LargeObject& o) { std::copy(o._data, o._data + SIZE, _data); }

		virtual ~LargeObject() {
			for (size_t i = 0; i < SIZE; ++i) {
				_data[i].~T();
			}
		}

		/// @brief 禁用赋值运算
		LargeObject& operator=(const LargeObject& o) {
			std::copy(o.data, o.data + SIZE, _data);
			return *this;
		};

		T& operator[](size_t index) {
			if (index >= SIZE) {
				throw std::out_of_range("index out of range");
			}
			return _data[index];
		}

		const T& operator[](size_t index) const {
			return const_cast<LargeObject*>(this)->operator[](index);
		}

		constexpr size_t size() const { return SIZE; }
	};
}

#endif // !__CPLUSPLUS_OOP_AFFINE_SMART_PTR_H
