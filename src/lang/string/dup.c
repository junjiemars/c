#include <_lang_.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


#ifndef NM_HAVE_STRDUP_FN
#include <stdlib.h>
char*
strdup(const char *s) {
	size_t size = sizeof(s)+1;
	char *d = malloc(size);
	return d ? memcpy(d, s, size) : 0;
}
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#ifdef NM_HAVE_STRDUP_FN

	char *s = strdup(argv[0]);
	assert((0 == strcmp(s, argv[0])) || "stdup() failed");

	free(s);

#endif
	

}
