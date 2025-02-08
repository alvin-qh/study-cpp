#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <memory.h>

#include "thread.h"

#define _max(a, b) ((a) > (b) ? (a) : (b))
#define _min(a, b) ((a) < (b) ? (a) : (b))

#define MAX_RESULT 100000

typedef struct
{
	pthread_t tid;
	uint32_t begin;
	uint32_t end;
	uint32_t result[MAX_RESULT];
	size_t result_count;
} thread_arg;

void* _calculate_primes_each_group(void* arg) {
	thread_arg* t_arg = (thread_arg*)arg;

	for (size_t n = t_arg->begin; n < t_arg->end; n++) {
		bool is_prime = true;

		for (size_t k = 2; k * k <= n; k++) {
			if (n % k == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			if (t_arg->result_count >= MAX_RESULT) {
				pthread_exit((void*)-1);
			}
			t_arg->result[t_arg->result_count++] = n;
		}
	}
	return (void*)0;
}

void _append_result(prime_result* result, thread_arg* arg) {
	size_t new_count = result->count + arg->result_count;

	uint32_t* new_result = (uint32_t*)malloc(sizeof(uint32_t) * new_count);
	if (result->count > 0) {
		memcpy(new_result, result->data, sizeof(uint32_t) * result->count);
	}
	memcpy(new_result + result->count, arg->result, sizeof(uint32_t) * arg->result_count);

	free((void*)result->data);

	result->data = new_result;
	result->count = new_count;
}

int calculate_primes(size_t count, prime_result* result) {
	const size_t g_count = count / GROUP_SIZE;

	thread_arg* t_args[g_count];

	for (size_t g = 0; g < g_count; g++) {
		thread_arg* arg = (thread_arg*)malloc(sizeof(thread_arg));
		arg->begin = _max(g * GROUP_SIZE, 2);
		arg->end = _min((g + 1) * GROUP_SIZE, count);
		arg->result_count = 0;

		pthread_t tid;
		int rc = pthread_create(&tid, NULL, _calculate_primes_each_group, arg);
		if (rc != 0) {
			return rc;
		}

		arg->tid = tid;
		t_args[g] = arg;
	}

	int rc = 0;
	for (size_t g = 0; g < g_count; g++) {
		if (rc == 0) {
			pthread_join(t_args[g]->tid, (void**)&rc);
			if (rc == 0) {
				_append_result(result, t_args[g]);
			}
		}
		else {
			pthread_join(t_args[g]->tid, NULL);
		}

		free((void*)t_args[g]);
	}
	return rc;
}

void free_result(prime_result* result) {
	free((void*)result->data);
	result->data = NULL;
	result->count = 0;
}
