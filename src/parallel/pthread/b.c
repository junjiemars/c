#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREADS 4

void *
echo(void *tid) {
	fprintf(stdout, "Hello, tid=%ld\n", (long)tid);
	pthread_exit(0);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	pthread_t t[N_THREADS];

	for (long i = 0; i < N_THREADS; i++) {
		fprintf(stdout, "creating thread %ld\n", i);
		int r = pthread_create(&t[i], 0, echo, (void*)i);
		if (r) {
			fprintf(stderr, "!panic, return code %d\n", r);
			return -1;
		}
	}
	pthread_exit(0);
	
	return 0;
}
