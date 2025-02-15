#pragma once

#ifndef __LINUX__IO_H
#define __LINUX__IO_H

#include <stdlib.h>

// `io.redirect.c` 实现函数

/// @brief 开始将指定的输出 IO 的文件描述符重定向到内存空间
///
/// 该函数的执行流程为:
///
/// 1. 将 `fileno` 参数表示的文件描述符进复制, 产生一个新文件描述符与 `fileno` 参数指向同一个文件;
/// 2. 创建一对管道文件描述符, 分别指向 "读管道" 和 "写管道", 并将 "读管道" 设置为 "非阻塞";
/// 3. 将 `fileno` 参数表示的文件描述符重定向到 "写管道", 令所有通过 `fileno` 文件描述符写入的数据实际被写入到 "写管道";
/// 4. 返回结构体实例, 包含上述产生的文件描述符;
///
/// @param fileno 输出 IO 文件描述符
/// @return 句柄指针, 本质上为 `memory_redirect` 结构体实例指针
void* fd_redirect_to_memory_begin(int fileno);

/// @brief 结束 IO 重定向, 返回 IO 被重定向期间, IO 输出的内容字符串
///
/// 该函数的执行流程为:
///
/// 1. 创建一个 "内存数据流", 得到该数据流的 `FILE*` 指针;
/// 2. 从 "读管道" 读取数据, 这些数据被写入到原始文件描述符, 并被重定向到 "写管道";
/// 3. 将读取的数据写入到 "内存数据流", 直到所有数据被读取;
/// 4. 恢复原始文件描述符原本的指向, 相当于恢复其重定向;
/// 5. 关闭相关的文件描述符和 "内存数据流";
///
/// @param h 句柄指针, 本质上为 `memory_redirect` 结构体实例指针
/// @return 字符串指针, 指向被重定向 IO 输出的内容
char* fd_redirect_to_memory_end(void* h, size_t* result_len);

#endif // !__LINUX__IO_H

