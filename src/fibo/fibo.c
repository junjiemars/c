#include "fibo.h"
#include <stdio.h>
#include <stdint.h>
#include <getopt.h>


#ifdef CL_HAVE_INTTYPES_H 
	#include <inttypes.h>
	#define outln_int64(s) printf("%" PRId64 "\n", s)
#else
	#define outln_int64(s) printf("%ld\n", s)
#endif

static struct option longopts[] = {
	{"help",    no_argument,    0,      'h'},
	{"static",  no_argument,    0,      's'},
	{"tail",    no_argument,    0,      't'},
	{0,         0,              0,       0}
};

static void usage(const char *p) {
	printf("usage %s\n", p);
	printf("  -h, --help\t\tthis help text\n");
	printf("  -s, --static\t\tcall static fibonacci routine\n");
	printf("  -t, --tail\t\tcall tail recursion fibonacci routine\n");
}


static int64_t fibo_static() {
	/*
	 * 1) if function exists then static vars in which exists;
	 * 2) C11 include a _Thread_local memory type for thread safe reson;
	 * 3) static vars initialized before main;
	 */
	static /*_Thread_local*/ int64_t first = 0;
	static /*_Thread_local*/ int64_t second = 1;
	int64_t out = first + second;
	first = second;
	second = out;
	return out;
}

static int64_t fibo_tail(int64_t n, int64_t a, int64_t b) {
	if (0 == n) return a;
	return fibo_tail(n-1, a+b, a);
}

int main(int argc, char * const argv[]) {
	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "hst", longopts, 0))) {
		switch (ch) {
			case 's':
				for (int i=0; i<10; i++) {
					outln_int64(fibo_static());
				}
				goto exit;
			case 't':
				outln_int64(fibo_tail(10, 1, 0));
				goto exit;
			case 'h':
			default:
				usage(argv[0]);
				goto exit;
		}
	}

	usage(argv[0]);

exit:
	return 0;
}
