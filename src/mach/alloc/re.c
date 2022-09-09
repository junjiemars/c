#include <_mach_.h>
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

void
illegle(void) {
	char *s = realloc(0, 0);
	printf("realloc(0, 0), %zu\n", malloc_size(s));
	free(s);
}

void
as_malloc(void) {
	char *s = realloc(0, sizeof(*s)*8);
	assert((0 != s) && strerror(errno));
	s[0] = 'A';
	if (0 == s[0]) {
		printf("realloc: zero-initialized\n");
	} else {
		printf("realloc: non zero-initialized\n");
	}
	free(s);
}

void
as_free(void) {
	char *s = calloc(8, sizeof(*s));
	assert((0 != s) && strerror(errno));
	s[0] = 'R';
	char **p = &s;
	printf("realloc: allocated = %zu\n", malloc_size(s));
	printf("realloc: +realloc = 0x%x\n", **p);

#if _RISKY_
	char *s1 = realloc(s, 0);
	printf("realloc: -realloc = 0x%x\n", **p);
	printf("realloc: freed? = %i\n", 0 == s1);
#else
	free(*p);
#endif  /* end of _RISKY_ */
}

void
enlarge(void) {
	int *i = calloc(8, sizeof(*i));
	assert((0 != i) && strerror(errno));
	printf("calloc: allocated = %zu\n", malloc_size(i));
	i[0] = 0x11223344;
	int **p = &i;
	printf("realloc: +realloc = 0x%x, @0x%p\n", **p, *p);
	int *i1 = realloc(i, sizeof(*i1)*8*2);
	assert((0 != i1) && strerror(errno));
	printf("realloc: -realloc = 0x%x, @0x%p\n", *i1, i1);
	free(i1);
}

void
shrink(void) {
	int *i = calloc(16, sizeof(*i));
	assert((0 != i) && strerror(errno));
	printf("calloc: allocated = %zu\n", malloc_size(i));
	i[15] = 0x11223344;
	int **p = &i;
	printf("realloc: +realloc = 0x%x, @0x%p\n", **p, *p);
	int *i1 = realloc(i, sizeof(*i1)*8);
	assert((0 != i1) && strerror(errno));
	printf("realloc: -realloc = 0x%x, @0x%p\n", *i1, i1);
	printf("realloc: copied? = %i\n", 0x11223344 == i1[7]);
	free(i1);
}

void
same(void) {
	char *s = calloc(8, sizeof(*s));
	assert((0 != s) && strerror(errno));
	printf("calloc: allocated = %zu\n", malloc_size(s));
	s[0] = 'R';
	printf("realloc: +realloc = 0x%x, @0x%p\n", *s, s);
	char *s1 = realloc(s, sizeof(*s)*8);
	assert((0 != s1) && strerror(errno));
	printf("realloc: -realloc = 0x%x, @0x%p\n", *s1, s1);
	free(s1);
}

int
main(void) {
	printf("illegle?\n--------------------\n");
	illegle();

	printf("as_malloc\n--------------------\n");
	as_malloc();

	printf("as_free\n--------------------\n");
	as_free();

	printf("enlarge\n--------------------\n");
	enlarge();

	printf("shrink\n--------------------\n");
	shrink();

	printf("same\n--------------------\n");
	same();

	return 0;
}
