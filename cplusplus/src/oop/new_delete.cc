#include "oop/new_delete.h"

inline void* __malloc(size_t n) {
    void* ptr = ::malloc(n);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

inline void __free(void* ptr, size_t n) {
    (void)n;
    ::free(ptr);
}

void* operator new(size_t n) { return __malloc(n); }

void* operator new[](size_t n) { return __malloc(n); }

void* operator new(size_t n, const std::nothrow_t&) noexcept { return ::malloc(n); }

void* operator new[](size_t n, const std::nothrow_t&) noexcept { return ::malloc(n); }

void operator delete(void* ptr) noexcept { return ::free(ptr); }

void operator delete[](void* ptr) noexcept { return ::free(ptr); }

void operator delete(void* ptr, const std::nothrow_t&) noexcept { return ::free(ptr); }

void operator delete[](void* ptr, const std::nothrow_t&) noexcept { return ::free(ptr); }

#ifdef __cpp_sized_deallocation
void operator delete(void* ptr, size_t n) noexcept { __free(ptr, n); }

void operator delete[](void* ptr, size_t n) noexcept { __free(ptr, n); }
#endif

namespace cxx::oop {
    using namespace std;

    NewDelete::NewDelete() : NewDelete("") { }

    NewDelete::NewDelete(const string& name) : _name(name) { }

    const string& NewDelete::name() const { return _name; }

    void* NewDelete::operator new(size_t n) { return __malloc(n); }

    void* NewDelete::operator new[](size_t n) { return __malloc(n); }

    void NewDelete::operator delete(void* ptr) noexcept { return ::free(ptr); }

    void NewDelete::operator delete[](void* ptr) noexcept { return ::free(ptr); }

} // namespace cxx::oop
