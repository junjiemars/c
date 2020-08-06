#include <_lang_.h>
#include <complex.h>
#include <stdio.h>

#if (MSVC)
#  pragma warning(disable: 4204)
#endif


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	double r = 1.0;
#if (MSVC)
  _Dcomplex z = { r, 2.0 };
#else
  double complex i = 2.0 * I;
	double complex z = r + i;
#endif
	printf("complex z = %.1f + %.1fi, sizeof(z) = %zu\n",
				 creal(z), cimag(z),
				 sizeof(z));
	
	return 0;
}
