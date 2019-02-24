#include <_algo_.h>
#include <stdio.h>

unsigned long
hash(const char *str) {
	unsigned long h = 0;
	int c;
	while ((c = *str++)) {
		h = c + (h << 6) + (h << 16) - h;
	}
	return h;
}

int
main(int argc, char **argv) {
	if (argc > 1) {
		unsigned long h = hash(argv[1]);
		printf("sdbm hash(\"%s\") = %zu\n", argv[1], h);
	}

	return 0;
}
