#include "oop/union.h"

#include <utility>

namespace cxx::oop {
    using namespace std;

    UnionData::UnionData() : UnionData(0) { }

    UnionData::UnionData(uint64_t v) : u64(v) { }

    UnionData::UnionData(uint32_t v1, uint32_t v2) : u32{ v1, v2 } { }

    UnionData::UnionData(
        uint16_t v1,
        uint16_t v2,
        uint16_t v3,
        uint16_t v4
    ) : u16{ v1, v2, v3, v4 } { }

    UnionData::UnionData(
        uint8_t v1,
        uint8_t v2,
        uint8_t v3,
        uint8_t v4,
        uint8_t v5,
        uint8_t v6,
        uint8_t v7,
        uint8_t v8
    ) : u8{ v1, v2, v3, v4, v5, v6, v7, v8 } { }

    UnionData::UnionData(UnionData&& o) :
        u64(exchange(o.u64, 0)) { }

    UnionData& UnionData::operator=(UnionData&& o) {
        if (this != &o) {
            u64 = exchange(o.u64, 0);
        }
        return *this;
    }

    bool UnionData::operator==(const UnionData& o) const { return u64 == o.u64; }

#if __ge_cxx20
    strong_ordering UnionData::operator<=>(const UnionData& o) const { return u64 <=> o.u64; }
#else
    bool UnionData::operator!=(const UnionData& o) const { return !(*this == o); }
    bool UnionData::operator<(const UnionData& o) const { return u64 < o.u64; }
    bool UnionData::operator>(const UnionData& o) const { return u64 > o.u64; }
    bool UnionData::operator<=(const UnionData& o) const { return u64 <= o.u64; }
    bool UnionData::operator>=(const UnionData& o) const { return u64 >= o.u64; }
#endif

} // namespace cxx::oop
