#include <_algo_.h>
#include <stdio.h>

/* Dan Bernstein */
unsigned long
hash(const char *str) {
	unsigned long h = 5381;
	int c;
	while (0 != (c = *str++)) {
		h = ((h << 5) + h) + c;
	}
	return h;
}

int
main(int argc, char **argv) {
	if (argc > 1) {
		unsigned long h = hash(argv[1]);
		printf("djb2 hash(\"%s\") = %lu\n", argv[1], h);
	}
	return 0;
}
