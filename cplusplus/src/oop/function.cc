#include "oop/function.h"

namespace cxx::oop {

#if __ge_cxx20

    int addition_with_named_parameters(int left, int right) {
        return left + right;
    }

#endif

} // namespace cxx::oop