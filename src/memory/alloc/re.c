#include <_memory_.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


#if defined(NM_HAVE_MALLOC_SIZE_FN)
#  if defined(DARWIN)
#    include <malloc/malloc.h>
#  elif defined(WINNT)
#    define malloc_size(x) _msize((x))
#  elif defined(LINUX)
#    include <malloc.h>
#    define malloc_size(x) malloc_usable_size((x))
#  endif
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	size_t n = sizeof(int)*sizeof(int);
	int *pi = calloc(n, sizeof(*pi));
	assert((0 != pi) && strerror(errno));
	assert((0 == pi[n-1]) && "fill with non-zero");
	printf("calloc() = %zu\n", malloc_size(pi));
	pi[n-1] = 0x11223344;

	/* enlarge */
	int *pii = realloc(pi, sizeof(*pi)*n*2);
	assert((0 != pii) && strerror(errno));
	assert((0x11223344 == pii[n-1]) && "0x11223344 not be copied");
#ifdef WINNT
	assert((0 != pii[n]) && "filled with zero");
#else
	assert((pii == pi) && "diff pointers");
	assert((0 == pii[n]) && "filled with non-zero");
#endif
	printf("realloc() = %zu\n", malloc_size(pii));
	pii[0] = 0x44332211;

	/* shrink */
	pi = realloc(pii, sizeof(*pi)*n/2);
	assert((0 != pi) && strerror(errno));
	assert((0x44332211 == pi[0]) && "0x44332211 not be copied");
#ifndef WINNT	
	assert((pii == pi) && "diff pointers");
#endif
	printf("realloc() = %zu\n", malloc_size(pi));

	/* on Windows, double free: */
	/* HEAP_CORRUPTION_ACTIONABLE_BlockNotBusy_DOUBLE_FREE_c0000374_memory_realloc.exe!main */
	free(pi);
}
