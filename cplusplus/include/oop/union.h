#pragma once

#ifndef __CPLUSPLUS_OOP__UNION_H
#define __CPLUSPLUS_OOP__UNION_H

#include <cstdint>

namespace cxx::oop {

	union UnionData {
		uint8_t u8[8];
		uint16_t u16[4];
		uint32_t u32[2];
		uint64_t u64;

		UnionData();

		UnionData(uint64_t v);

		UnionData(uint32_t v1, uint32_t v2);

		UnionData(uint16_t v1,
			uint16_t v2,
			uint16_t v3,
			uint16_t v4
		);

		UnionData(
			uint8_t v1,
			uint8_t v2,
			uint8_t v3,
			uint8_t v4,
			uint8_t v5,
			uint8_t v6,
			uint8_t v7,
			uint8_t v8
		);

		UnionData(const UnionData&) = default;

		UnionData(UnionData&& o);

		UnionData& operator=(const UnionData&) = default;

		UnionData& operator=(UnionData&&);

		bool operator==(const UnionData& o) const;

		std::strong_ordering operator<=>(const UnionData& o) const;
	};

} // ! namespace cxx::oop

#endif // !__CPLUSPLUS_OOP__UNION_H
