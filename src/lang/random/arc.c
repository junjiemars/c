#include <_lang_.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t
randomize(const uint32_t n) {
	return arc4random_uniform(n);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	size_t n = 10;
	if (argc > 1) {
		n = atoi(argv[1]);
	}
	printf("arc random: [0, %zu)\n", n);
	printf("--------------------\n");
	for (size_t i = 0; i < n; i++) {
		printf("%u ", randomize(n));
	}
	putchar('\n');
	return 0;
}
