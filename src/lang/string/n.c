#include <_lang_.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#if defined(NM_HAVE_STRN__FN)

	const char *xxx = "xxxxxxxx";
	size_t len = strnlen(xxx, 16);
	char *x = malloc(sizeof(char)*(len+1));
	
	char *s = strncpy(x, xxx, len+1);
	assert((0 == strncmp(s, xxx, len)) || "strncpy() failed");
#if NDEBUG
	_unused_(s);
#endif
	
	/* If count is reached before the entire array src was copied,
		 the resulting character array is not null-terminated. */
	memset(x, 0, len+1);
	assert((0 == x[8]) || "0 not at end");

	x[3] = 'Z';
	strncpy(x, xxx, 3);
	assert(('Z' == x[3]) || "copied 0 at end");

	/* If, after copying the terminating null character from src,
		 count is not reached, additional null characters
		 are written to dest until the total of count characters
		 have been written. */
	memset(x, 'z', len+1);
	assert(('z' == x[len+1]) || "'z' not at end");

	strncpy(x, "xxx", len+1);
	assert((0 == x[len+1]) || "0 not at end");

	/* The behavior is undefined:
		 1) if the character arrays overlap,
		 2) if either dest or src is not a pointer to a character
		 array (including if dest or src is a null pointer),
		 3) if the size of the array pointed to by dest is
		 less than count, or
		 4) if the size of the array pointed to by src is less
		 than count and it does not contain a null character */

	free(x);

#endif	
}
