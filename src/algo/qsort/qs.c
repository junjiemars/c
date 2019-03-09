#include <_algo_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static char *ss[] = {
	"ccc",
	"bb",
	"aaaaa",
};

static int ii[] = {
	0x44,
	0x33,
	0x11,
	0x22,
};

int
cmp_str(const void *s1, const void *s2) {
	return strcmp(*(char* const*)s1, *(char* const*)s2);
}

void
sort_str(char **ss, const size_t size) {
	qsort(ss, size, sizeof(*ss), cmp_str);
	for (int i = 0; i < (int)size; i++) {
		printf("%s\n", ss[i]);
	}
}

int
cmp_int(const void *i1, const void *i2) {
	return *(int const*)i1 - *(int const*)i2;
}

void
sort_int(int *ii, const size_t size) {
	qsort(ii, size, sizeof(*ii), cmp_int);
	for (int i = 0; i < (int)size; i++) {
		printf("0x%x\n", ii[i]);
	}
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);
	sort_str(ss, sizeof(ss)/sizeof(*ss));
	sort_int(ii, sizeof(ii)/sizeof(*ii));
	return 0;
}
