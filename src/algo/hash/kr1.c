#include <_algo_.h>
#include <stdio.h>

unsigned long
hash (const char *str) {
	unsigned long h = 0;
	int c;
	while (0 != (c = *str++)) {
		h += c;
	}
	return h;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		unsigned long h = hash(argv[1]);
		printf("K&R hash1(\"%s\") = %lu\n", argv[1], h);
	}
	
	return 0;
}
