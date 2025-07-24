#include "stl/optional/func.h"

namespace cxx::stl {

#if __ge_cxx17
    optional<int> check_even_number(int n) {
        if (n % 2 == 0) {
            return n;
        }
        return std::nullopt;
    }
#endif

} // namespace cxx::stl
