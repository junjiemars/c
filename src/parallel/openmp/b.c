#include "_parallel_.h"
#include <stdio.h>

#ifdef NM_HAVE_OPENMP
#  include <omp.h>
#endif

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

#ifdef NM_HAVE_OMP_GET_NUM_PROCS_FN
	printf("procs[%i]\n----------\n", omp_get_num_procs());
#endif

#ifdef NM_HAVE_OPENMP
#  pragma omp parallel
#endif
	printf("In omp\n");

	return 0;
}
