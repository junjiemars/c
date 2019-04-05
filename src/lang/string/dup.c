#include <_lang_.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if MSVC
/* warning C4996: 'strdup': The POSIX name for this item is
	 deprecated. Instead, use the ISO C and C++ conformant name:
	 _strdup */
#  pragma warning(disable : 4996)
#endif


#ifndef NM_HAVE_STRDUP_FN
char*
strdup(const char *s) {
	char *d = malloc(strlen(s)+1);
	return d ? strcpy(d, s) : 0;
}
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	char *s = strdup(argv[0]);
	assert((0 == strcmp(s, argv[0])) && "stdup() failed");
#ifdef NM_HAVE_STRDUP_FN
	printf("strdup: %s\n", s);
#else
	printf("strdup*: %s\n", s);
#endif
	
	free(s);
	return 0;
}
