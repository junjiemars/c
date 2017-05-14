#include <stdio.h>

#define _unused_(x) ((void)(x))

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	int i=1, j=2;
	int *pi = &i, *pj = &j;
	int **ppi = &pi;
	*ppi = pj;
	
	printf("ppi=%p\n", ppi);
}
