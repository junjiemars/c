#include <_memory_.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

void
foo(void) {
	int *pi = calloc(10, sizeof(int));
	assert((0 != pi) && strerror(errno));
	pi[0] = 0x11223344;
	assert((0 == pi[1]) && "filled with non-zero");

	free(pi);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);
	foo();
	return 0;
}
