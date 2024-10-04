/**
 * 测试公共部分
 */
#pragma once

#ifndef __CPLUSPLUS_TEST_H
#define __CPLUSPLUS_TEST_H

#include <sys/types.h>

namespace cpp {
	/// @brief 对浮点数进行指定小数位数保留
	/// @param n 浮点数数值
	/// @param fixed 要保留的小数位数
	/// @return 保留小数后的结果
	double number_to_fixed(double n, uint fixed);
} // ! namespace cpp

#endif // ! __CPLUSPLUS_TEST_H
