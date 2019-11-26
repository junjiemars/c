#include <_lang_.h>
#include <complex.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	double i = 2.0 * I;
	double r = 1.0;
	double complex z = r + i;
	printf("complex z = %.1f + %.1fi, sizeof(z) = %zu\n",
				 creal(z), cimag(z),
				 sizeof(z));
	
	return 0;
}
