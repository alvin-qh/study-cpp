#include "stl/optional/func.h"

namespace cxx::stl {

    optional<int> check_even_number(int n) {
        if (n % 2 == 0) {
            return n;
        }
        return std::nullopt;
    }

}
