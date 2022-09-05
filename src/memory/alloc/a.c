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

static void test_alloca(void);

int
main(void)
{
	test_alloca();
}


void
#if (NM_HAVE_ALLOCA_FN)
test_alloca(void)
{
	int *pi = alloca(sizeof(int) * 10);
	assert((0 != pi) && strerror(errno));
	pi[0] = 0x11223344;
	/* depend on implementation */
	/* assert((0 == pi[1]) && "filled with non-zero"); */
}

#else
test_alloca(void)
{
  /* void */
}

#endif
