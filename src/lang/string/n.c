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

char *
self_strncpy(char *dst, const char *src, size_t n) {
	char *r = dst;
	while (0 != (*dst++ = *src++) && n--);
	return r;
}

int
self_strncmp(const char *s1, const char *s2, size_t n) {
	while (*s1 && (*s1 == *s2) && n > 1) {
		s1++, s2++, n--;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
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
	memset(buf, 0x11, sizeof(buf)/sizeof(*buf));
	assert(0x11 == buf[7] && "strncpy, 0x11 != <tailing>");
	
	/* if N > strlen(src) then padding 0 */
	strncpy(buf, "abc", sizeof(buf)/sizeof(*buf) /* N */);
	assert(0 == buf[7] && "strncpy(), N > strlen(src)");

	/* if N < strlen(src), N is reached before the entire array 
		 src was copied, the tailing characters keep unchanged, 
		 so the resulting character array is may not be null-terminated.
	*/
	memset(buf, 0x11, sizeof(buf)/sizeof(*buf));
	strncpy(buf, "abc", 1 /* N */);
	assert('a' == buf[0] && 0x11 == buf[7] && "strncpy(), N < strlen(src)");

	/* The behavior is undefined:
		 1) if the character arrays overlap,
		 2) if either dest or src is not a pointer to a character
		 array (including if dest or src is a null pointer),
		 3) if the size of the array pointed to by dest is
		 less than N, or
		 4) if the size of the array pointed to by src is less
		 than N and it does not contain a null character 
	*/
}

void
test_strncmp(void) {
	char *s1 = "abcdefg", *s2 = "abcdefG";
	int cmp1 = strncmp(s1, s2, strlen(s2));
	int cmp2 = self_strncmp(s1, s2, strlen(s2));
	assert(0 < cmp1 && 0 < cmp2 && "strncmp(), failed");
	cmp1 = strncmp(s1, s2, strlen("abcdef"));
	cmp2 = self_strncmp(s1, s2, strlen("abcdef"));
	assert(0 == cmp1 && 0 == cmp2 && "strncmp(), failed");
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
	test_strncmp();
#endif	
}
