#include <_io_.h>
#include <stdio.h>
 
int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);
	
	int n = 0;
	char c;
	if (0 < (n = fscanf(stdin, "%c", &c))) {
		printf("c=%c [%i]\n", c, c);
	}

	int i;
	if (0 < (n = fscanf(stdin, "%i", &i))) {
		printf("i=%i\n", i);
	}

	long l;
	if (0 < (n = fscanf(stdin, "%li", &l))) {
		printf("l=%li\n", l);
	}

	float f;
	if (0 < (n = fscanf(stdin, "%f", &f))) {
		printf("f=%f\n", f);
	}

	double d;
	if (0 < (n = fscanf(stdin, "%lf", &d))) {
		printf("d=%lf\n", d);
	}
}

