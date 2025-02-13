#pragma once

#ifndef __LINUX__IO_H
#define __LINUX__IO_H

// `io.redirect.c` 实现函数

void close_file_redirect(void* h);

void* fd_redirect_to_memory_begin(int fileno);
char* fd_redirect_to_memory_end(void* h);

#endif // !__LINUX__IO_H

