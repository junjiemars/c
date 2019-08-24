#include <_memory_.h>
#include <stdlib.h>

#if NM_HAVE_POSIX_MEMALIGN_FN
#  if DARWIN || LINUX
void *
_malign_(size_t alignment, size_t size) {
	void *p;
	int n = posix_memalign(&p, alignment, size);
	return 0 == n ? p : 0;
}
#  endif
#elif NM_HAVE_MEMALIGN_FN
void *
_malign_(size_t alignment, size_t size) {
	void *p = memalign(alignment, size);
	return p;
}
	
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
