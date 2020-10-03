#include <_unicode_.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <string.h>

#if MSVC
#  pragma warning(disable : 4996)
#endif

void print_wc(const wchar_t *s);
void wc_to_mb(const wchar_t *s);
void wcs_to_mbs(const wchar_t *s, size_t n);

void
print_wc(const wchar_t *s) {
	const wchar_t *p = s;
	while (*p) {
		printf("[%lc]", *p++);
	}
	putchar('\n');
}

void
wc_to_mb(const wchar_t *s) {
	char buf[MB_LEN_MAX];
	while (*s) {
		memset(buf, 0, MB_LEN_MAX);
		int len = wctomb(buf, *s);
		printf("[%s/%i]", buf, len);
		s++;
	}
	putchar('\n');
}

void
wcs_to_mbs(const wchar_t *s, size_t n) {
	char *buf = calloc(n, sizeof(*buf));
	size_t len = wcstombs(buf, s, n);
	printf("%s/%zu\n", buf, len);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("current locale: %s\n", setlocale(LC_ALL, 0));
  printf("set locale to native: %s\n", setlocale(LC_ALL, ""));
#if (WINNT)
  printf("set locale to native: %s\n", setlocale(LC_ALL, "en_US.UTF-8"));
#endif
	printf("sizeof(wchar_t): %zu bytes\n", sizeof(wchar_t));
	printf("MB_LEN_MAX: %i\n", MB_LEN_MAX);
	printf("----------\n");

	wchar_t s[] = L"abc中文def";
	printf("%ls:\n", s);
	printf("----------\n");
	
	print_wc(s);
	wc_to_mb(s);
	wcs_to_mbs(s, sizeof(s));
	return 0;
}
