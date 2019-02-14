#include <_io_.h>
#include <stdio.h>
 
int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	char c;
	int i;
	long l;
	float f;
	double d;
	
	int n = fscanf(stdin, "%c, %i, %li, %f, %lf",
								 &c, &i, &l, &f, &d);
	printf("scanned count: %d\n", n);
	printf("c=%c, i=%i, li=%li, f=%f, lf=%lf\n",
				 c, i, l, f, d);

	return 0;
}

