#include <_lang_.h>
#include <stdio.h>

void
f1(int *p1, int *p2, int *val) {
	*p1 += *val;
	*p2 += *val;
}

#if NM_HAVE_RESTRICT_KEYWORD
void
f2(int *restrict p1, int *restrict p2, int *restrict val) {
	*p1 += *val;
	*p2 += *val;
}
#endif

int
main(int argc, char **argv) {
	_unused_(argv);

	int x = argc;
	int y = argc * 10;
	int z = argc * 100;
	
	f1(&x, &y, &z);
	printf("x=%d, y=%d, z=%d\n", x, y, z);
#if NM_HAVE_RESTRICT_KEYWORD
	f2(&x, &y, &z);
	printf("x=%d, y=%d, z=%d\n", x, y, z);
#endif
	return 0;
}
