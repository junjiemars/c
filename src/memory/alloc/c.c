#include <_memory_.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>


static void test_calloc(void);


int
main(void)
{
	test_calloc();
	return 0;
}


void
test_calloc(void)
{
	int *pi = calloc(10, sizeof(*pi));
	assert((0 != pi) && strerror(errno));
	pi[0] = 0x11223344;
	assert((0 == pi[1]) && "filled with non-zero");
	free(pi);
}
