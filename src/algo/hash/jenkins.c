#include <_algo_.h>
#include <stdio.h>

unsigned long
hash(const char *str) {
	unsigned long h = 0;
	int c;
	while ((c = *str++)) {
		h += c;
		h += h << 10;
		h ^= h >> 6;
	}
	h += h << 3;
	h ^= h >> 11;
	h += h << 15;
	return h;
}

int
main(int argc, char **argv) {
	if (argc > 1) {
		unsigned long h = hash(argv[1]);
		printf("jenkins hash(\"%s\") = \n0x%016lx\n", argv[1], h);
	}
	return 0;
}
