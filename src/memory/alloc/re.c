#include <_memory_.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	size_t n = sizeof(int)*4;
	int *pi = calloc(n, sizeof(*pi));
	assert((0 == pi) || strerror(errno));
	assert((0 == pi[n-1]) || "fill with non-zero");
	printf("calloc() = %zu\n", _msize(pi));
	pi[n-1] = 0x11223344;

	/* enlarge */
	int *pii = realloc(pi, 4*n*2);
	assert((pii == pi) || strerror(errno));
	assert((0x11223344 == pii[n-1]) || "0x11223344 not be copied");
	assert((0 != pii[n]) || "filled with zero");
	printf("realloc() = %zu\n", _msize(pii));

	/* shrink */
	pi = realloc(pii, sizeof(*pi)*n/2);
	assert((pii == pi) || strerror(errno));
	assert((0 == pi[0]) || "0x0 not be copied");
	printf("realloc() = %zu\n", _msize(pi));

	/* on Windows, double free: */
	/* HEAP_CORRUPTION_ACTIONABLE_BlockNotBusy_DOUBLE_FREE_c0000374_memory_realloc.exe!main */
	free(pi);
}
