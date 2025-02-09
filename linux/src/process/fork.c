#include "process.h"

#include <unistd.h>
#include <sys/wait.h>
#include <memory.h>

#ifndef byte_t
typedef unsigned char byte_t;
#endif

/// @brief 表示管道数组下标的枚举
typedef enum __pipe_type {
	READ = 0, // 下标 `0` 表示管道的读句柄
	WRITE,	  // 下标 `1` 表示管道的写句柄
} pipe_type;

worker_t execute_worker(worker_func worker, fork_msg* msg) {
	// 定义管道句柄数组, 包含两个管道句柄, 下标 `0` 表示读句柄, 下标 `1` 表示写句柄
	int pfds[2];

	// 建立管道, 并返回一对管道句柄, 保存到 `pfds` 数组中
	if (pipe(pfds) != 0) {
		abort();
	}

	// 启动子进程, 父子进程代码将在这里产生分叉
	pid_t pid = fork();
	if (pid < 0) {
		// 如果 `fork` 函数返回负数, 表示子进程创建失败
		abort();
	}

	if (pid > 0) {
		// 如果 `fork` 函数返回大于 `0` 的值, 表示子进程创建成功, 且当前代码在父进程中执行
		// 由于父进程只对管道进行 "读" 操作, 故可提前将 "写" 句柄关闭
		close(pfds[WRITE]);

		// 从管道读取 `MSG_SIZE` 字节的信息, 并确认读取字节数
		ssize_t n = read(pfds[READ], (void*)msg, MSG_SIZE);
		if (n != MSG_SIZE) {
			abort();
		}

		// 读取结束, 关闭管道 "读" 句柄
		close(pfds[READ]);

		int stat;

		// 等待指定进程结束, 其参数含义如下:
		// - `pid`: 该参数的值将影响 `waitpid` 函数的行为, 可选值如下:
		//     - `pid < -1`: 等待 "进程组号" 为 `pid` 参数绝对值的任意子进程, 即该参数的含义是 `-进程组 ID`;
		//     - `pid = -1`: 等待任何子进程, 此时 `waitpid` 函数相当于 `wait` 函数;
		//     - `pid = 0`: 等待进程组号和当前进程相同的任意子进程结束;
		//     - `pid > 0`: 等待进程 ID 为所给指定值的进程结束;
		// - `stat_loc`: 一个 16 位整数指针, 用于获取子进程结束的原因, 该参数可以为 `NULL` 值, 表示不关心子进程结束原因;
		//   该参数返回的值的低 8 位表示子进程是否正常结束, 高 8 位表示子进程退出的状态值, 可以通过如下一系列宏进行该值的判断:
		//	   - `WIFEXITED`: 判断进程是否正常结束, 即子进程主函数通过 `exit` 函数或 `return` 关键字结束, 而非通过
		//       `abort` 函数或其它信号值结束
		//	   - `WIFSIGNALED`: 判断子进程是否因为接收到信号而终止;
		//	   - `WIFSTOPPED`: 判断子进程是否因为信号而被暂停执行;
		//	   - `WEXITSTATUS`: 获取正常结束的子进程的状态值, 即子进程主函数通过 `exit` 函数或 `return` 关键字返回的值;
		//	   - `WTERMSIG`: 获取导致子进程结束的信号值;
		//	   - `WSTOPSIG`: 获取导致子进程暂停的信号值;
		// - `options`: 提供额外的控制选项, 包括:
		//     - `0`: 不进行额外控制;
		//     - `WNOHANG`: 如果子进程未结束, 则 `waitpid` 函数立即返回 `0` 值, 而不发生阻塞;
		//     - `WUNTRACED`: 如果子进程进入暂停状态, 则立即返回;
		// `waitpid` 函数返回其等待成功的子进程的进程号 (`pid`), 用于表示那个进程被结束
		if (waitpid(pid, &stat, 0) != pid) {
			abort();
		}

		// 主进程返回返回值
		worker_t w = {
			1,
			{ pid },
			{ stat },
		};
		return w;
	}
	else {
		// 如果 `fork` 函数返回等于 `0` 的值, 表示代码在子进程中执行
		// 由于子进程只对管道进行 "写" 操作, 故可提前将 "读" 句柄关闭
		close(pfds[READ]);

		// 通过函数指针执行指定函数, 该函数将在子进程内存空间中执行
		int retcode = worker(pfds[WRITE]);

		// 子进程函数执行完毕, 关闭管道 "写" 句柄
		close(pfds[WRITE]);

		// 通过 `exit` 函数和函数返回值结束子进程
		// `exit` 参数值可以通过 `waitpid` 函数的第二个参数返回, 并通过 `WEXITSTATUS` 宏获取该值
		exit(retcode);
	}
}

worker_t worker_groups(worker_func worker, size_t proc_n, fork_msg* msgs) {
	worker_t w = { 0 };

	if (proc_n >= 16) {
		return w;
	}

	w.size = proc_n;

	// 定义管道句柄数组, 包含两个管道句柄, 下标 `0` 表示读句柄, 下标 `1` 表示写句柄
	int pfds[2];

	// 建立管道, 并返回一对管道句柄, 保存到 `pfds` 数组中
	if (pipe(pfds) != 0) {
		abort();
	}

	for (size_t i = 0; i < proc_n; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			// 如果 `fork` 函数返回负数, 表示子进程创建失败
			abort();
		}
		else if (pid > 0) {
			// 如果 `fork` 函数返回大于 `0` 的值, 表示子进程创建成功, 且当前代码在父进程中执行
			// 记录子进程 pid
			w.pids[i] = pid;

			// 设置子进程分组
			setpgid(pid, w.pids[0]);
		}
		else {
			// 如果 `fork` 函数返回等于 `0` 的值, 表示代码在子进程中执行
			if (i == 0) {
				// 如果是第一个子进程, 则关闭管道 "读" 句柄
				close(pfds[READ]);
			}
			// 执行子进程入口函数
			int retcode = worker(pfds[WRITE]);
			exit(retcode);
		}
	}

	close(pfds[WRITE]);
}
