#include <_mp_.h>
#include <stdlib.h>
#include <stdio.h>

#if NM_HAVE_OMP_H
#  include <omp.h>
#endif

double
calc_pi(int n) {
	double pi, sum = 0.0, step;
	double x;
	int i;

	step = 1.0 / (double) n;

#if NM_HAVE_OMP_H
/* msvc error C3015: initialization in OpenMP 'for' statement has
	 improper form.
	 openmp does not know c99's for loop.
*/
#  pragma omp parallel for reduction(+:sum) private(x)
#endif
	
	for (i = 1; i <= n; i++) {
		x = (i - 0.5) * step;
		sum = sum + 4.0 / (1.0 + x*x);
	}

	_unused_(x);
	pi = step * sum;
	return pi;
}


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int n = 100;
	if (argc > 1) {
		n = atoi(argv[1]);
	}
	double pi = calc_pi(n);
	printf("pi=%f via %i times calc\n", pi, n);
	
	return 0;
}
