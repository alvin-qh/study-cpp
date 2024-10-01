#pragma once

#ifndef __CPLUSPLUS_REFERENCE_MOVE_H
#define __CPLUSPLUS_REFERENCE_MOVE_H

#include <memory>

namespace cpp {
	using namespace std;

	/// @brief 可移动类型
	///
	/// 可移动类型即可通过 “右值引用” 构造器 (或 “右值引用” 赋值运算符)
	/// 将实例从一个变量移动到另一个变量.
	///
	/// 可移动类型在将其 “临时变量” 赋值到另一个变量 (例如从函数返回) 时,
	/// 具备更高的性能.
	///
	/// @tparam T
	template<typename T, typename _Alloc = allocator<T>>
	class Moveable {
		typedef Moveable<T, _Alloc> Self;
	private:
		T* _ptr;
		size_t _len;

		_Alloc _alloc;

		/// @brief 根据所给值以及长度设置当前对象
		///
		/// @param val 所给值
		/// @param len 所需长度
		void _from_value(const T& val, size_t len) {
			T* ptr = _alloc.allocate(len);

			for (size_t i = 0; i < len; ++i) {
				new(ptr + i) T(val);
			}

			_ptr = ptr;
			_len = len;
		}

		/// @brief 销毁指向指向的内存空间
		void _free() {
			if (_ptr) {
				T* ptr = _ptr;
				_ptr = nullptr;

				size_t len = _len;
				_len = 0;

				for (size_t i = 0; i < len; ++i) {
					(ptr + i)->~T();
				}

				_alloc.deallocate(ptr, len);
			}
		}

	public:
		/// @brief 默认构造器
		Moveable() :
			_ptr(nullptr),
			_len(0) {
		}

		/// @brief 参数构造器
		///
		/// @param val 所给值
		Moveable(const T& val) {
			_from_value(val, 1);
		}

		/// @brief 参数构造器
		///
		/// @param val 所给值
		/// @param len 所需长度
		Moveable(const T& val, size_t len) {
			_from_value(val, len);
		}

		/// @brief 删除拷贝构造器
		// Moveable(const Moveable&) = delete;

		/// @brief 移动构造器
		///
		/// 默认的 “移动构造器” 和 “拷贝构造器” 功能一致, 无法起到 "移动" 对象的作用.
		///
		/// `Motivate(Motivate&&) noexcept = default`
		///
		/// 如果需要真正的移动对象, 则需要自定义移动构造器.
		///
		/// @param o 被复制对象
		Moveable(Moveable&& o) noexcept :
			_ptr(o._ptr),
			_len(o._len) {
			// 完成移动后, 对源对象进行处理, 防止其销毁已转移的资源
			o._ptr = nullptr;
			o._len = 0;
		};

		/// @brief 析构函数
		virtual ~Moveable() {
			_free();
		}

		/// @brief 取消复制运算符重载
		Self& operator=(const Self&) = delete;

		/// @brief 重载赋值运算符以 "移动" 对象
		///
		/// @param o 被移动对象
		/// @return 当前对象的引用
		Self& operator=(Self&& o) noexcept {
			// 销毁当前对象引用的资源
			_free();

			// 移动源对象引用的资源
			_ptr = o._ptr;
			_len = o._len;

			// 处理源对象, 避免其销毁已移动的资源
			o._ptr = nullptr;
			o._len = 0;

			return *this;
		}

		/// @brief 重载解引运算符, 获取指针指向的值的可变引用
		///
		/// @return 指针指向的值的可变引用
		T& operator*() { return *_ptr; }

		/// @brief 重载解引运算符, 获取指针指向的值的只读引用
		///
		/// @return 指针指向的值的只读引用
		const T& operator*() const { return *_ptr; }

		/// @brief 重载下标运算符
		///
		/// @param index 下标索引值
		/// @return 下标索引值对应的值的可变引用
		T& operator[](size_t index) { return _ptr[index]; }

		/// @brief 重载下标运算符
		///
		/// @param index 下标索引值
		/// @return 下标索引值对应的值的只读引用
		const T& operator[](size_t index) const { return _ptr[index]; }

		/// @brief 获取集合长度
		///
		/// @return 集合长度值
		size_t size() const { return _len; }

		/// @brief 判断对象是否有效
		///
		/// @return 是否有效
		bool valid() const { return _ptr != nullptr; }
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_REFERENCE_MOVE_H
