#include <_lang_.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#if defined(NM_HAVE_STRN_ANY_FN)

size_t
self_strnlen(const char *s, size_t n) {
	size_t len = 0;
	while (*s++ && n--) {
		len++;
	}
	return len;
}

void
test_strnlen(void) {
	char buf[8];
	memset(buf, 0, sizeof(buf)/sizeof(*buf));
	size_t len, len1, len2;
	len1 = strnlen(buf, sizeof(buf)/sizeof(*buf));
	len2 = self_strnlen(buf, sizeof(buf)/sizeof(*buf));
	assert(0 == len1 && 0 == len2);
	len = strlen("abc");
	strncpy(buf, "abc", len);
	len1 = strnlen(buf, sizeof(buf)/sizeof(*buf));
	len2 = self_strnlen(buf, sizeof(buf)/sizeof(*buf));
	assert(len == len1 && len == len2);
	len = strlen("abcdefgh");
	strncpy(buf, "abcdefgh", len-1);
	len1 = strnlen(buf, len-1);
	len2 = self_strnlen(buf, len-1);
	assert(len-1 == len1 && len-1 == len2);
}

void
test_strncpy(void) {
	char buf[8];
	memset(buf, 0x11, sizeof(buf)/sizeof(buf[0]));
	assert(0x11 == buf[7] && "strncpy, 0x11 != tailing");
	
	/* if num > src then padding 0
		 If count is reached before the entire array src was copied,
		 the resulting character array is not null-terminated. 
	*/
	strncpy(buf, "abc", sizeof(buf)/sizeof(buf[0]) /* num */);
	assert(0 == buf[7] && "strncpy, 0 != padding");

	/* if num < strlen(src), dest will not null-terminated
		 If, after copying the terminating null character from src,
		 count is not reached, additional null characters
		 are written to dest until the total of count characters
		 have been written. 
	*/
	strncpy(buf, "abcdefgh", sizeof(buf)/sizeof(buf[0]));
	assert('h' == buf[7] && "strncpy, 'h' != tailing");

	/* The behavior is undefined:
		 1) if the character arrays overlap,
		 2) if either dest or src is not a pointer to a character
		 array (including if dest or src is a null pointer),
		 3) if the size of the array pointed to by dest is
		 less than count, or
		 4) if the size of the array pointed to by src is less
		 than count and it does not contain a null character 
	*/
}

void
test_strncmp(void) {
	char buf[8];
	strncpy(buf, "abcdefg", sizeof(buf)/sizeof(buf[0]));
	int cmp = strncmp(buf, "abcdefX", sizeof(buf)/sizeof(buf[0]));
	assert(0 < cmp && "strncmp, cmp > 0");
	/* buf is not null-terminated */
	strncpy(buf, "abcdefgh", sizeof(buf)/sizeof(buf[0]));
	cmp = strncmp(buf, "abcdefghX", sizeof(buf)/sizeof(buf[0]));
	assert(0 == cmp && "strncmp, 0 != cmp");
}


#endif /* end of NM_HAVE_STRN_ANY_FN */

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#if ! defined(NM_HAVE_STRN_ANY_FN)
	printf("skip strn* fn testing\n");
#else
	printf("ddd\n");
	test_strnlen();
	test_strncpy();
	test_strncmp();
#endif	
}
