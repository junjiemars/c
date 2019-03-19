#include <_parallel_.h>
#include <stdio.h>

#if NM_HAVE_OMP_H
#  include <omp.h>
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("procs[%i]\n----------\n", omp_get_num_procs());
#pragma omp parallel
	printf("In omp\n");
	
	return 0;
}
