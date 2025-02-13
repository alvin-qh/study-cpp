#include "io.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct __file_redirect {
	int fno;
	int dup;
} file_redirect;

inline static void _close_file_redirect(file_redirect* fr) {
	if (fr) {
		if (fr->dup >= 0) {
			close(fr->dup);
		}
		free(fr);
	}
}

typedef struct __memory_redirect {
	struct __file_redirect _fr;
	int fd[2];
} memory_redirect;

inline static void _close_memory_redirect(memory_redirect* mr) {
	if (mr) {
		if (mr->fd[0] && mr->fd[1]) {
			close(mr->fd[0]);
			close(mr->fd[1]);
		}
		close_file_redirect((file_redirect*)mr);
	}
}

inline static int _duplicate_fileno(file_redirect* fr, int fileno) {
	fr->fno = fileno;
	fr->dup = dup(fileno);

	return fr->dup < 0 ? -1 : 0;
}

void* fd_redirect_to_memory_begin(int fileno) {
	memory_redirect* mr = (memory_redirect*)calloc(1, sizeof(memory_redirect));
	if (_duplicate_fileno(&mr->_fr, fileno) != 0) {
		_close_memory_redirect(mr);
	}

	if (pipe(mr->fd) < 0) {
		_close_memory_redirect(mr);
	}

	dup2(mr->fd[1], fileno);
	return mr;
}

inline static int _copy_fd(int src, FILE* target) {
	char buf[128];
	ssize_t n, len = 0;
	while ((n = read(src, buf, sizeof(buf))) > 0) {
		fwrite(buf, 1, n, target);
		len += n;
	}

	return len;
}

char* fd_redirect_to_memory_end(void* h) {
	if (!h) {
		return NULL;
	}

	memory_redirect* mr = (memory_redirect*)h;

	char* result;
	size_t len;
	FILE* fp = open_memstream(&result, &len);

	_copy_fd(mr->fd[0], fp);
	fclose(fp);

	dup2(mr->_fr.dup, mr->_fr.fno);
	_close_memory_redirect(mr);

	return result;
}
