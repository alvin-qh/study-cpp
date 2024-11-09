#include "stl/optional/func.h"

namespace cxx::stl {

#if (__cplusplus >= 201703L)
    optional<int> check_even_number(int n) {
        if (n % 2 == 0) {
            return n;
        }
        return std::nullopt;
    }
#endif // ! (__cplusplus >= 201703L)
}
