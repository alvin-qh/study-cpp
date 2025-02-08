#pragma once

#ifndef __CPLUSPLUS__TEST_H
#define __CPLUSPLUS__TEST_H

#include <cstdint>

namespace cxx {

	/// @brief 对浮点数进行指定小数位数保留
	///
	/// @param n 浮点数数值
	/// @param fixed 要保留的小数位数
	/// @return 保留小数后的结果
	double number_to_fixed(double n, uint32_t fixed);

} // namespace cxx

#endif // __CPLUSPLUS__TEST_H
