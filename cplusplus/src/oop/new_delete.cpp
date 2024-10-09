#include "oop/new_delete.hpp"

void* operator new(size_t n) {
	void* ptr = ::malloc(n);
	if (!ptr) {
		throw std::bad_alloc();
	}
	return ptr;
}

void* operator new(size_t n, std::nothrow_t&) noexcept {
	return ::malloc(n);
}

void operator delete(void* ptr) noexcept {
	return ::free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept {
	(void)size;
	return ::free(ptr);
}

namespace cpp {
}
