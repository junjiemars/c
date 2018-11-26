#include <_unicode_.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#if MSVC
#  pragma warning(disable : 4996)
#endif

int
main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	wchar_t s[] = L"abc中文def\n";
	wchar_t *p = s;
	char buffer[MB_LEN_MAX];
	
	while (*p) {
		int len = wctomb(buffer, *p);
		if (len < 1) break;
		for (int i=0; i < len; ++i) {
			printf("[%c]", buffer[i]);
			++p;
		}
	}
}
