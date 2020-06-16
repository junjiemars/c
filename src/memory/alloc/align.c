#include <_memory_.h>


#if (DARWIN || LINUX)
#  if LINUX && !__USE_XOPEN2K
#    define __USE_XOPEN2K 1
#  endif
#  include <stdlib.h>
#elif (WINNT)
#  include <malloc.h>
#endif




int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	int *p = 0;

#if NM_HAVE_ALIGNED_ALLOC_FN
	p = aligned_alloc(1024, 4096);

#elif NM_HAVE_POSIX_MEMALIGN_FN
	posix_memalign((void **)&p, 1024, 4096);

#endif

	if (p) {
		free(p);
	}

	return 0;
}
