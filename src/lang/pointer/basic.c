#include "_lang_.h"
#include <stdio.h>


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	int i=1, j=2;
	int *pi = &i, *pj = &j;
	int **ppi = &pi;
	*ppi = pj;
	
	printf("ppi@%p=%i\n", ppi, **ppi);
}
