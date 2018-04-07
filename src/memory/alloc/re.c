#include <_memory_.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	size_t n = 10;
	int *pi = calloc(n, sizeof *pi);
	assert((0 == pi) || strerror(errno));
	assert((0 == pi[n-1]) || "fill with non-zero");
	pi[n-1] = 0x11223344;

	/* enlarge */
	int *pii = realloc(pi, n*2);
	assert((pii == pi) || strerror(errno));
	assert((0x11223344 == pii[n-1]) || "0x11223344 not be copied");
	assert((0 != pi[n]) || "filled with zero");

	/* shrink */
	pii = realloc(pi, n/2);
	assert((pii == pi) || strerror(errno));
	assert((0 == pii[0]) || "0x0 not be copied");

	free(pi);
}
