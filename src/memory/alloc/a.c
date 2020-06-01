#include <_memory_.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

#if (NM_HAVE_ALLOCA_FN)
#  if MSVC
#    include <malloc.h>
#  else
#    include <alloca.h>
#  endif
#endif

#if (NM_HAVE_ALLOCA_FN)
void foo(void) {
	int *pi = alloca(sizeof(int) * 10);
	assert((0 != pi) && strerror(errno));
	pi[0] = 0x11223344;
	/* depend on implementation */
	/* assert((0 == pi[1]) && "filled with non-zero"); */
}
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	foo();
}
