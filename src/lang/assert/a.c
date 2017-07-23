#include <_lang_.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int
sqr(int x) {
	assert((0 < x) && (x < 100));
	return (x * x);
}

int
main(int argc, const char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	assert((argc > 1) && "usage: one <int>");
	
	#if (NM_HAVE_STATIC_ASSERT)
		static_assert(4 == sizeof(int), "sizeof(int) != 4 bytes");
		printf("sizeof(int)=%lu\n", sizeof(int));
	#endif

	if (argc > 1) {
		int n = atoi(argv[1]);
		printf("sqr(%u)=%u\n", 2u, sqr(n));
		printf("after call sqr()\n");
	}

	return 0;
}
