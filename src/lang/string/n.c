#include <_lang_.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#if defined(NM_HAVE_STRN_ANY_FN)

void test_strnlen(void) {
	char buf[8] = "abc";
	size_t len = strnlen(buf, sizeof(buf)/sizeof(buf[0]));
	assert(3 == len && "strnlen, 3 != len");
	strncpy(buf, "abcdefgh", sizeof(buf)/sizeof(buf[0]));
	len = strnlen(buf, sizeof(buf)/sizeof(buf[0]));
	assert(8 == len && "strnlen, 8 != len");
}

void test_strncpy(void) {
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


#endif /* end of NM_HAVE_STRN_ANY_FN */

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#if ! defined(NM_HAVE_STRN_ANY_FN)
	printf("skip strn* fn testing\n");
#else
	test_strnlen();
	test_strncpy();
#endif	
}
