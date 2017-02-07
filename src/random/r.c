#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define _unused_(x) ((void)(x))

size_t
randomize(size_t n) {
	size_t r = rand() % n;	
	return r;
}

int
main(int argc, const char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	srand(time(0));
	
	size_t n = 100;
	for (size_t i=0; i<n; ++i) {
		printf("%zu ", randomize(n));
	}
	putchar('\n');

	return 0;
}
