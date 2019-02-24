#include <_algo_.h>
#include <stdio.h>

unsigned long
hash(const char *str) {
	unsigned long h;
	for (h = 0; *str; str++) {
		h = *str + 31 * h;
	}
	return h % 1024;
}

int
main(int argc, char **argv) {
	if (argc > 1) {
		unsigned long h = hash(argv[1]);
		printf("K&R hash2(\"%s\") = %zu\n", argv[1], h);
	}
	return 0;
}
