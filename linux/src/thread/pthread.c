#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#include "thread.h"

#define _max(a, b) ((a) > (b) ? (a) : (b))
#define _min(a, b) ((a) < (b) ? (a) : (b))

typedef struct
{
	pthread_t tid;
	uint32_t begin;
	uint32_t end;
	uint32_t result[10000];
	size_t result_count;
} thread_arg;

void* _calculate_primes_each_group(void* arg) {
	thread_arg* t_arg = (thread_arg*)arg;

	for (size_t n = t_arg->begin; n < t_arg->end; n += 2) {
		bool is_prime = true;
		for (size_t k = t_arg->begin; k * k <= t_arg->end; k += 2) {
			if (n % k == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			t_arg->result[t_arg->result_count++] = n;
		}
	}
	return NULL;
}

int calculate_primes(size_t count, prime_result* result) {
	const size_t g_count = count / GROUP_SIZE;
	const thread_arg* t_args[g_count];

	for (size_t g = 0; g_count < 20; g++) {
		thread_arg* arg = malloc(sizeof(thread_arg));
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

	for (size_t g = 0; g < g_count; g++) {
		pthread_join(t_args[g]->tid, NULL);
		free((void*)t_args[g]);
	}

	return 0;
}
