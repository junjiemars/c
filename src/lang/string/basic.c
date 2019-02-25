#include <_lang_.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


size_t
self_strlen(const char *s) {
  size_t len = 0;
  while (*s++) {
    len++;
  }
  return len;
}

int
self_strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++, s2++;
  }
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *
self_strcpy(char *dst, const char *src) {
  char *r = dst;
  while (0 != (*dst++ = *src++));
  return r;
}

void
test_strlen(char *s) {
	size_t len1 = strlen(s);
  size_t len2 = self_strlen(s);
  assert((len1 == len2) || "self_strlen() failed");
#if NDEBUG
	_unused_(len1);
	_unused_(len2);
#endif
}

void
test_strcpy(void) {
	char buf[8];
	int len = sizeof(buf)/sizeof(buf[0]);
	memset(buf, 0x11, len);
	assert(0x11 == buf[len-1] && "strcpy(), 0x11 != tailing");

	/* does not pad tailing 0 */
	strcpy(buf, "abc");
	assert(0 == buf[strlen(buf)] && "strcpy(), 0 != tailing");
	assert(0x11 == buf[len-1] && "strcpy(), 0x11 != tailing");

	/* no null-terminated */
	/* msvc runtime error:
		 Security check failure or stack buffer overrun - code c0000409 (!!! second chance !!!)
		 *** WARNING: Unable to verify checksum for lang_string_basic.exe
		 d:\agent\_work\3\s\src\vctools\crt\vcstartup\src\gs\gs_report.c(220)+0x5
		 lang_string_basic!__report_gsfailure+0x1c:
		 00007ff6`8dc67788 cd29            int     29h
	 */
	/* lang_string_basic[2834:14486] detected buffer overflow */
	strcpy(buf, "abcdefgh");
	assert(0 != buf[len-1] && "strcpy(), 0 == tailing");
}

void
test_strcmp(char *s) {
	size_t len = strlen(s);
	char *d1 = malloc(len+1);
  char *d2 = strcpy(d1, s);
	assert(d1 == d2 && "strcpy(), diff between dest and retval");
  assert(0 == strcmp(s, d1) && "strcpy(), failed");
	assert(0 == self_strcmp(d1, d2) && "strcpy(), failed");
#if NDEBUG
	_unused_(d2);
#endif
	free(d1);
}

void
test_strcmp1(void) {
	char buf[8];
	size_t len = sizeof(buf)/sizeof(buf[0]);
	const char *s = "abx";
	memset(buf, 0x11, len);
  strcpy(buf, "abc");
	assert(0 > strcmp(buf, s) && "strcmp(), failed");
	assert(0 > self_strcmp(buf, s) && "self_strcmp(), failed");
	assert(0 < self_strcmp(s, buf) && "self_strcmp(), failed");
}

#define STRCMP(a, R, b) (strcmp((a), (b)) R 0)
/* 0 == strcmp(a, b)
	 => !strcmp(a, b)
	 => STRCMP(a, ==, "volatile")
 */

void
test_STRCMP(void) {
	char *a = "abcd";
	char *b = "abcd";
	assert(STRCMP(a, ==, b) && "STRCMP, a != b");
#if NDEBUG
	_unused_(a);
	_unused_(b);
#endif
}

int
main(int argc, char **argv) {
  _unused_(argc);

	test_strlen(argv[0]);
	test_strcpy();
/* 	test_strcmp(argv[0]); */
/* 	test_strcmp1(); */
/* 	test_STRCMP(); */

	return 0;
}
