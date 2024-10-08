#pragma once

#ifndef __CPLUSPLUS_OPP_NEW_DELETE_H
#define __CPLUSPLUS_OPP_NEW_DELETE_H

#include <memory>

void* operator new(size_t n);

namespace cpp {
	void* __malloc(size_t n);
	void __free(void* ptr);

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
