#include <_lang_.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#if MSVC
#  pragma warning(disable: 4244)
#endif


size_t
randomize(size_t n /* RAND_MAX */) {
	size_t r = rand() % n;	
	return r;
}

int
ranged_randomize(int min, int max) {
	int r = rand() / (RAND_MAX + 1.0) * (max - min) + min;
	return r;
}

int
main(int argc, char **argv) {
	/* initialize random number generator */
	srand(time(0));

	size_t n;

	if (4 == argc) {
		n = atoi(argv[1]);
		int min = atoi(argv[2]);
		int max = atoi(argv[3]);

		printf("raw random [%i, %i)\n", min, max);
		printf("--------------------\n");
		for (size_t i = 0; i < n; i++) {
			printf("%i ", ranged_randomize(min, max));
		}
		putchar('\n');
	} else if (argc > 1) {
		n = atoi(argv[1]);
		printf("raw random [%i, %zu)\n", 0, n);
		printf("--------------------\n");
		for (size_t i = 0; i < n; i++) {
			printf("%zu ", randomize(n));
		}
		putchar('\n');
	}
	

	return 0;
}
