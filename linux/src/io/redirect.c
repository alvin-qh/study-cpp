#include "io.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

/// @brief 定义结构体, 保存 IO 重定向到文件的信息
typedef struct __file_redirect {
	int fno; // 被重定向的原始 IO 文件描述符, 例如 `STDOUT_FILENO`
	int dup; // 从原始 IO 文件描述符复制的新描述符, 与原始描述符指向同一个文件
} file_redirect;

/// @brief 关闭 `file_redirect` 结构体存储的相关句柄
///
/// `file_redirect` 结构体中存储了被重定向的原始 IO 文件描述符 (`fno` 字段) 和原始
/// IO 文件描述符的副本文件描述符 (`dup` 字段)
///
/// 之后 `fno` 字段存储的的文件描述符会被重定向 (即令其指向新的文件数据结构),
/// 而 `dup` 字段存储的文件描述符仍引用着原始文件数据结构
///
/// 本函数的作用是将 `fno` 存储的文件描述符关闭, 并将其重新定向到 `dup`
/// 字段保存描述符所指向的文件数据结构上, 相当于恢复 `fno` 文件描述符原始文件指向
///
/// @param fr 指向 `file_redirect` 结构体实例的指针
inline static void _close_file_redirect(file_redirect* fr) {
	if (fr) {
		if (fr->dup >= 0) {
			// 将 `file_redirect` 结构体实例中 `dup` 字段保存的描述符复制到原始 IO 描述符中
			//
			// `dup2` 函数用于将参数 1 (表示一个文件描述符) 复制到参数 2 (表示另一个文件描述符) 中
			//
			// 如果函数参数 2 表示的文件描述符引用了一个未关闭的文件数据结构, 则先将其关闭,
			// 之后令其引用到和参数 1 相同的文件结构上, 即 `dup2` 函数执行完毕后, 参数 2
			// 文件描述符的指向会发生变化, 指向和参数 1 相同的文件结构
			dup2(fr->dup, fr->fno);

			// 关闭从原始 IO 描述符中复制的描述符
			close(fr->dup);
		}
		free(fr);
	}
}

/// @brief 定义结构体, 用于将 IO 重定向到内存空间
typedef struct __memory_redirect {
	struct __file_redirect _fr; // 基础自 `file_redirect` 结构体实例
	int fd[2]; // 定义一对管道文件描述符, 其中 `fd[1]` 将用于 IO 重定向, `fd[0]` 用于读取写入到 IO 中的内容
} memory_redirect;

/// @brief 关闭 `memory_redirect` 结构体中存储的文件描述符
///
/// 该结构体从 `file_redirect` 结构体继承, 即存储了被重定向 IO 的文件描述符指向和重定向前原始 IO 文件描述符指向的副本
///
/// 该结构体中还存储了一对管道文件描述符 (`fd` 字段), 其中 `fd[1]` 用于对原始 IO 文件描述符进行重定向,
/// 重定向后, 所有写入原始 IO 文件描述符的数据将通过管道传递给 `fd[0]`, 并可通过 `fd[0]` 读取内容
///
/// @param mr 指向 `memory_redirect` 结构体实例的指针
inline static void _close_memory_redirect(memory_redirect* mr) {
	if (mr) {
		if (mr->fd[0]) {
			// 关闭管道读文件描述符
			close(mr->fd[0]);
		}
		if (mr->fd[1]) {
			// 关闭管道写文件描述符
			close(mr->fd[1]);
		}
		_close_file_redirect((file_redirect*)mr);
	}
}

/// @brief 将 `fileno` 参数表示的 IO 文件描述符进行复制
///
/// 该函数将 `fileno` 表示的 IO 文件描述符保存到 `file_redirect` 结构体的 `fno` 字段中,
/// 并创建其副本保存到 `dup` 字段中
///
/// 之后 `fno` 字段存储的的文件描述符会被重定向, 而 `dup` 字段仍存储着原始 IO 文件描述符
///
/// @param fr 指向 `file_redirect` 结构体实例的指针
/// @param fileno 表示原始 IO 文件描述符整数值
/// @return `0` 表示成功, 其它值表示失败
inline static int _duplicate_fileno(file_redirect* fr, int fileno) {
	// 保存原始 IO 文件描述符, 之后该描述符会被重定向
	fr->fno = fileno;

	// 保存原始 IO 文件描述符的副本, 该副本用于在结束时恢复原始 IO 文件描述符
	//
	// `dup` 函数用于从已有的文件描述符创建出一个新的文件描述符 (相当于复制),
	// 返回的新文件描述符与原文件描述符共享同一个文件数据结构, 共享相同的锁,
	// 共享读写指针位置和标志位
	//
	// `dup` 函数是 `fcntl(oldfd, F_DUPFD, 0)` 函数调用的简化版本
	//
	// `dup` 函数返回新的文件描述符, 为一个整数值, 如果返回的数值小于 0,
	// 则表示返回错误
	fr->dup = dup(fileno);
	if (fr->dup < 0) {
		perror("cannot duplicate source file description");
		return -1;
	}
	return 0;
}

void* fd_redirect_to_memory_begin(int fileno) {
	// 分配内存地址, 指向 `memory_redirect` 结构体实例
	memory_redirect* mr = (memory_redirect*)calloc(1, sizeof(memory_redirect));

	// 将 `fileno` 变量表示的文件描述符和其副本存储到 `memory_redirect` 结构体实例中
	if (_duplicate_fileno(&mr->_fr, fileno) != 0) {
		_close_memory_redirect(mr);
	}

	// 创建一对管道, 将管道描述符存入 `memory_redirect` 结构体实例的 `fd` 字段中
	if (pipe(mr->fd) < 0) {
		_close_memory_redirect(mr);
	}

	// 将 "读管道" 设置为 "非阻塞"
	fcntl(mr->fd[0], F_SETFL, fcntl(mr->fd[0], F_GETFL) | O_NONBLOCK);

	// 修改 `fileno` 变量存储文件描述符的指向, 令其指向 "写管道"
	//
	// 这一步完成后, 所有向 `fileno` 描述符执行文件写入的内容, 都会重定向到 "写管道" 中,
	// 并可通过 "读管道" 进行读取
	dup2(mr->fd[1], fileno);

	return mr;
}

/// @brief 将文件描述符指向的文件内容写入到指定的文件中
///
/// 本函通过 `read` 函数从 `fd` 文件描述符指向的文件中读取数据,
/// 并将读取到的数据写入到 `fp` 指针指向的文件流中
///
/// 不断重复上述过程, 直到 `fd` 文件描述符指向的文件读取到末尾
///
/// 由于数据写入的目标是文件流 (`fp` 参数), 故调用该函数后,
/// 要让数据立即写入文件, 需要通过 `fflush` 函数对文件流进行刷新,
/// 或通过 `fclose` 函数关闭文件流
///
/// @param fd 表示一个文件描述符, 将通过该描述符, 读取对应文件的内容
/// @param fp 表示一个文件流, 会将读取到的内容写入到该描述符中
/// @return 总共写入的数据长度
size_t _copy_fd_into_file(int fd, FILE* fp) {
	char buf[128] = "\0";
	ssize_t n, len = 0;

	// 从 `fd` 文件描述符指向的文件读取数据, 每次最大读取 `128` 个字符,
	// 并写入 `buf` 数组中
	// 如果 `read` 函数返回 `0`, 则 `fd` 文件描述符指向的文件已经读取到末尾
	// (`EOF`), 否则返回实际读取到的数据长度
	//
	// 对于 `STDOUT_FILENO` 文件描述符 (即标准输出文件描述符, 值为 `1`),
	// 如果该文件描述符为阻塞模式, 则 `read` 函数不会返回 `0` 值,
	// 而是发生阻塞, 直到有新的可读取数据被读取; 此时可将文件描述符设置为
	// "非阻塞", 从而保证 `read` 函数可以返回 `0` 值,
	// 表示已经将之前输出的数据全部读取
	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		// 将读取到的数据写入文件流中
		fwrite(buf, 1, n, fp);

		// 计算总体读取到的数据长度
		len += n;
	}

	return len;
}

char* fd_redirect_to_memory_end(void* h, size_t* res_len) {
	if (!h) {
		return NULL;
	}

	memory_redirect* mr = (memory_redirect*)h;

	// 创建一个内存流, 返回表示该流的 `FILE*` 指针
	char* res = NULL;
	FILE* fp = open_memstream(&res, res_len);

	// 将数据从读管道读取后写入内存流
	size_t cp_len = _copy_fd_into_file(mr->fd[0], fp);

	// 关闭内存流
	fclose(fp);

	// 关闭 `memory_redirect` 结构体实例
	_close_memory_redirect(mr);

	// 确认拷贝数据的长度和内存数据流分配的长度一致
	assert(*res_len == cp_len);

	return res;
}
