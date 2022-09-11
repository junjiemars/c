#include "_parallel_.h"
#include <stdio.h>

#if (NM_HAVE_OPENMP)
#  include <omp.h>
#endif

int
main(void)
{
#if (NM_HAVE_OMP_GET_NUM_PROCS)
	printf("procs[%i]\n----------\n", omp_get_num_procs());
#endif

#if (NM_HAVE_OPENMP)
#  pragma omp parallel
#endif

	printf("In omp\n");

	return 0;
}
