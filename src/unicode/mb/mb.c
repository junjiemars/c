#include <_unicode_.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

#if MSVC
#  pragma warning(disable : 4996)
#endif

int
main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	wchar_t s[] = L"abc中文def";
	setlocale(LC_ALL, "");
	printf("%ls/%zu:\n", s, sizeof(wchar_t));
	printf("----------\n");

	wchar_t *p = s;
	while (*p) {
		printf("[%lc]", *p++);
	}
	putchar('\n');
	return 0;
}
