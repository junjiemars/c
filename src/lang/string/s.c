#include <_lang_.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#if defined(NM_HAVE_STR__S_FN)

	const char *xxx = "xxxxxxxx";
	size_t len = strlen(xxx);
	char *x = malloc(sizeof(char)*(len+1));

	errno_t e = strcpy_s(x, sizeof(char)*(len+1), xxx);
	assert((0 == e) && (0 == strcmp(x, xxx)) || "strcpy_s() failed");
#if NDEBUG
	_unused_(e);
#endif
	free(x);

#endif
}
