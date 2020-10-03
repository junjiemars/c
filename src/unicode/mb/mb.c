#include <_unicode_.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <string.h>

#if MSVC
#  pragma warning(disable:4996)
#endif

size_t mbstrlen(const char *s);
void print_wcs(const wchar_t *ws);
size_t mbs_to_wcs(wchar_t *ws, const char *s, size_t ns);
void wc_to_mb(const wchar_t *ws);
void wcs_to_mbs(const wchar_t *ws, size_t n);

size_t
mbstrlen(const char *s) {
  size_t mblen;
  size_t n = 0;
  mbstate_t mbs;

  memset(&mbs, 0, sizeof(mbs));
  while ((mblen = mbrlen(s, MB_CUR_MAX, &mbs)) != 0
         && mblen != (size_t)-1
         && mblen != (size_t)-2) {
    s += mblen;
    n++;
  }
  return n;
}

void
print_wcs(const wchar_t *ws) {
	const wchar_t *p = ws;
	while (*p) {
		printf("[%lc]", *p++);
	}
	putchar('\n');
}

size_t
mbs_to_wcs(wchar_t *ws, const char *s, size_t ns) {
  if (!s) {
    return 0;
  }

  size_t n = mbstowcs(ws, s, ns);
  if (n == (size_t)-1) {
    perror("!panic");
    return 0;
  }
  return n;
}

void
wc_to_mb(const wchar_t *ws) {
	char buf[MB_LEN_MAX];
	while (*ws) {
		memset(buf, 0, MB_LEN_MAX);
		int len = wctomb(buf, *ws);
    if (-1 == len) {
      perror("!panic");
      return;
    }
		printf("[%s/%i]", buf, len);
		ws++;
	}
	putchar('\n');
}

void
wcs_to_mbs(const wchar_t *ws, size_t n) {
	char *buf = calloc(n, sizeof(*buf));
	size_t len = wcstombs(buf, ws, n);
  if ((size_t)-1 == len) {
    perror("!panic");
  }
	printf("mbstr=%s/%zu\n", buf, len);
  free(buf);
}

int
main(int argc, char **argv) {
	printf("current locale: %s\n", setlocale(LC_ALL, 0));
  printf("set locale to native: %s\n", setlocale(LC_ALL, ""));
#if (WINNT)
  printf("set locale to native: %s\n", setlocale(LC_ALL, "en_US.UTF-8"));
#endif
	printf("sizeof(wchar_t): %zu bytes\n", sizeof(wchar_t));
	printf("MB_LEN_MAX: %i\n", MB_LEN_MAX);
	printf("MB_CUR_MAX: %i\n", MB_CUR_MAX);
	printf("----------\n");

  if (argc < 2) {
    printf("where the input string?\n");
    return 0;
  }
  printf("%s\n", argv[1]);
	printf("----------\n");

  size_t sstrlen = strlen(argv[1]);
  size_t smblen = mbstrlen(argv[1]);
  printf("strlen=%zu, mbstrlen=%zu\n", sstrlen, smblen);
  
  wchar_t *ws = calloc(sstrlen + 1, sizeof(wchar_t));
  size_t n = mbs_to_wcs(&ws[0], argv[1], sstrlen + 1);
	printf("wcs=%ls\n", ws);

	print_wcs(ws);
	wc_to_mb(ws);
	wcs_to_mbs(ws, sizeof(wchar_t) * n);

  free(ws);
	return 0;
}
