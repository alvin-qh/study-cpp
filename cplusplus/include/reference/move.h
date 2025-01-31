#pragma once

#ifndef __CPLUSPLUS_REFERENCE__MOVE_H
#define __CPLUSPLUS_REFERENCE__MOVE_H

#include <utility>

namespace cxx::reference {

	/// @brief 可移动类型
	///
	/// 可移动类型即可通过 “右值引用” 构造器 (或 “右值引用” 赋值运算符)
	/// 将实例从一个变量移动到另一个变量
	///
	/// 可移动类型在将其 “临时变量” 赋值到另一个变量 (例如从函数返回) 时,
	/// 具备更高的性能.
	template<typename T>
	class Moveable {
		typedef Moveable<T> Self;

	public:
		/// @brief 默认构造器
		Moveable() : _ptr(nullptr) { }

		/// @brief 参数构造器
		///
		/// @param val 所给值
		Moveable(const T& val) : _ptr(new T(val)) { }

		/// @brief 删除拷贝构造器
		Moveable(const Moveable&) = delete;

		/// @brief 移动构造器
		///
		/// 默认的 “移动构造器” 和 “拷贝构造器” 功能一致, 无法起到 "移动" 对象的作用.
		///
		/// `Motivate(Motivate&&) noexcept = default`
		///
		/// 如果需要真正的移动对象, 则需要自定义 "移动构造器".
		///
		/// 在该 "移动构造器" 中, 将源对象 `o` 中存储的指针转移到当前对象,
		/// 并在源对象中将指针设置为 `null` 以避免析构销毁
		///
		/// @param o 被复制对象
		Moveable(Moveable&& o) noexcept : _ptr(std::exchange(o._ptr, nullptr)) { }

		/// @brief 析构函数
		virtual ~Moveable() {
#if __ge_cxx17
			if (T* ptr = std::exchange(_ptr, nullptr); ptr) {
#else
			T* ptr = std::exchange(_ptr, nullptr);
			if (ptr) {
#endif
				delete ptr;
			}
			}

		/// @brief 删除复制运算符
		Self& operator=(const Self&) = delete;

		/// @brief 重载赋值运算符以 "移动" 对象
		///
		/// @param o 被移动对象
		/// @return 当前对象的引用
		Self& operator=(Self && o) noexcept {
			// 调用析构函数必须通过 `this` 指针
			this->~Moveable();
			_ptr = std::exchange(o._ptr, nullptr);

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

		/// @brief 重载布尔运算符, 确定指针有效
		///
		/// @return 指针是否有效
		operator bool() const { return _ptr != nullptr; }

	private:
		T* _ptr;
		};

	} // namespace cxx::reference

#endif // __CPLUSPLUS_REFERENCE__MOVE_H
