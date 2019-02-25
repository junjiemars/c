#include <_lang_.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#if NM_HAVE_RAND_S_FN
#  if MSVC
#    define _CRT_RAND_S
#  endif
#endif
#include <stdlib.h>

#if NM_HAVE_RAND_S_FN
int
ranged_randomize(int min, int max) {
	unsigned int x;
	errno_t e = rand_s(&x);
	if (e) {
		return UINT_MAX;
	}
	x = (unsigned int)(x / (UINT_MAX + 1.0) * (max - min) + min);
	return x;
}
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#if NM_HAVE_RAND_S_FN
	printf("rand_s [-10, 10)\n");
	printf("--------------------\n");
	for (int i = 0; i < 10; i++) {
		printf("%i ", ranged_randomize(-10, 10));
	}
	putchar('\n');
#endif
	
	return 0;
}
