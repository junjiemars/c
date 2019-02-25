#include <_lang_.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#if MSVC
#  pragma warning(disable: 4244)
#endif


size_t
randomize(const size_t n /* RAND_MAX */) {
	size_t r = rand() % n;	
	return r;
}

int
main(int argc, char **argv) {
	/* initialize random number generator */
	srand(time(0));

	size_t n = 10;
	if (argc > 1) {
		n = atoi(argv[1]);
	}

	printf("raw random [%i, %zu)\n", 0, n);
	printf("--------------------\n");
	for (size_t i = 0; i < n; i++) {
		printf("%zu ", randomize(n));
	}
	putchar('\n');

	return 0;
}
