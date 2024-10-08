#include "oop/new_delete.hpp"

namespace cpp {
	void* __malloc(size_t n) {
		return ::malloc(n);
	}

	void __free(void* ptr) {
		return ::free(ptr);
	}


}

void* operator new(size_t n) {
	return cpp::__malloc(n);
}
