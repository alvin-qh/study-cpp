#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

extern "C" {

const char *hello_str();

void free_str(const char *ptr);

}  // extern "C"
