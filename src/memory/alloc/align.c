#include <_memory_.h>

#if NM_HAVE_MEMALIGN_FN
#  if (GCC)
#    include <malloc.h>
#    define _malign_ memalign
#  endif
#elif NM_HAVE_POSIX_MEMALIGN_FN
#  if (GCC)
#    include <stdlib.h>
#    define _malign_ posix_memalign
#  endif
#endif


int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

#if NM_HAVE_MEMALIGN_FN || NM_HAVE_MEMALIGN_FN
	int *p = _malign_(4096, 4096);
	if (p) {
		free(p);
	}
#endif

	return 0;
}
