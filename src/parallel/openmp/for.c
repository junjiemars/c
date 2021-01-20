#include <_parallel_.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef NM_HAVE_OPENMP
#  include <omp.h>
#endif

#if (MSVC)
#  pragma warning (disable : 4996)
#endif  /* end of MSVC */

double calc_pi(long n);

double
calc_pi(long n)
{
	double pi, sum = 0.0, step;
	double x;
	long i;

	step = 1.0 / (double)n;

#ifdef NM_HAVE_OPENMP
  /* msvc error C3015: initialization in OpenMP 'for' statement has
     improper form.
     openmp does not know c99's for loop.
  */
#  pragma omp parallel for reduction(+:sum) private(x)
#endif

	for (i = 1; i <= n; i++)
    {
      x = (i - 0.5) * step;
      sum = sum + 4.0 / (1.0 + x*x);
    }

	_unused_(x);
	pi = step * sum;
	return pi;
}


int
main(int argc, char **argv)
{
	long n = 100L;
	if (argc < 2 || 1 != sscanf(argv[1], "%li", &n))
    {
      perror(0);
      return 1;
    }

	double pi = calc_pi(n);
	printf("pi=%3.10lf via %li times calc\n", pi, n);
	
	return 0;
}
