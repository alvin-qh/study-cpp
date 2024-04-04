#pragma once

#ifndef __CONVERT_NUMSYS_H
#define __CONVERT_NUMSYS_H

#include "common.h"

#define ERR_BUF_NOT_ENOUGH (-1)
#define ERR_NUM_CANNOT_NEGATIVE (-2)

/**
 * 将整数转为二进制字符串
 *
 * Args:
 *  - `num` 整数值
 *  - `buf` 保存结果字符串的缓冲区指针
 *  - `buflen` 保存结果字符串的缓冲区长度
 *
 * Returns:
 *  - `0` 表示成功, 非 `0` 表示缓冲区长度不足
 */
int to_bin(int num, char* buf, size_t buflen);

/**
 * 将整数转为十六进制字符串
 *
 * Args:
 *  - `num` 整数值
 *  - `buf` 保存结果字符串的缓冲区指针
 *  - `buflen` 保存结果字符串的缓冲区长度
 *
 * Returns:
 *  - `0` 表示成功, 非 `0` 表示缓冲区长度不足
 */
int to_hex(int num, char* buf, size_t buflen);

/**
 * 将整数转为 Excel 列标识
 *
 * Excel 列标识规则为
 *  - 第 `0` 列标识为 `A`, 第 `1` 列为 `B`, ..., 以此类推, 直到第 `25` 列为 `Z`;
 *  - 第 `26` 列标识为 `AA`, 第 `27` 列为 `AB`, ..., 以此类推, 直到第 `` 列为 `ZZ`;
*/
int to_excel_column(int num, char* buf, size_t buflen);

#endif
