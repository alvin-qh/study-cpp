#pragma once

#ifndef __CPLUSPLUS_OPP_NEW_DELETE_H
#define __CPLUSPLUS_OPP_NEW_DELETE_H

#include <memory>

/// @brief 重载 `new` 操作符, 为单个对象分配内存
///
/// 该 `new` 操作符当内存分配失败后, 会抛出异常
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
void* operator new(size_t n);

/// @brief 重载 `new[]` 操作符, 为一系列对象分配内存
///
/// 该 `new[]` 操作符当内存分配失败后, 会抛出异常
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
void* operator new[](size_t n);

/// @brief 重载 `new` 操作符, 为单个对象分配内存
///
/// 该 `new` 操作符当内存分配失败后, 不会抛出异常, 返回 `nullptr`
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
void* operator new(size_t n, const std::nothrow_t&) noexcept;

/// @brief 重载 `new` 操作符, 为单个对象分配内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
void* operator new[](size_t n, const std::nothrow_t&) noexcept;


/// @brief 重载 `new` 操作符, 为单个对象分配内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
void operator delete(void* ptr) noexcept;

/// @brief 重载 `new` 操作符, 为单个对象分配内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
void operator delete(void* ptr, const std::nothrow_t&) noexcept;

/// @brief 重载 `new` 操作符, 为单个对象分配内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
void operator delete(void* ptr, size_t n) noexcept;

namespace cpp {
	template <typename T>
	class allocator {
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
	public:
		allocator() noexcept {}
		~allocator() noexcept {}

		allocator& operator=(const allocator&) noexcept;
		allocator& operator=(allocator&&) noexcept;

		pointer allocate(size_type n);
		void deallocate(pointer p, size_type n);
		template <typename U, typename... Args>
		void construct(U* p, Args&&... args);
		template <typename U>
		void destroy(U* p);
	};
}

#endif // ! __CPLUSPLUS_OPP_NEW_DELETE_H
