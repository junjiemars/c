#include <_algo_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static char *ss[] = {
	"a1 9 2 3 1",
	"g1 act car",
	"zo4 4 7",
	"ab1 off key dog",
	"a8 act zoo",
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
show_ss(const char *title, char **aa, const size_t size) {
	printf("%s ss\n----------\n", title);
  for (size_t i = 0; i < size; i++) {
		printf("%s\n", aa[i]);
	}
	printf("----------\n");
}

void
sort_str(char **aa, const size_t size) {
	show_ss("raw", aa, size);
	qsort(aa, size, sizeof(*aa), cmp_str);
	show_ss("sorted 1th", aa, size);
}

void
sort_str_2th(char **aa, const size_t size) {
	for (size_t i = 0; i < size; i++) {
		size_t pre = 0, n = 0;
		for (size_t j = 0; j < strlen(aa[i]); j++) {
			if (' ' == aa[i][j]) {
				if (n < 1) {
					pre = j+1;
					n++;
				} else {
					aa[i] = &aa[i][pre];
					break;
				}
			}
		}
	}
	show_ss("raw 2th", aa, size);
	qsort(aa, size, sizeof(*aa), cmp_str);
	show_ss("sorted 2th", aa, size);
}

int
cmp_int(const void *i1, const void *i2) {
	return *(int const*)i1 - *(int const*)i2;
}

void
sort_int(int *aa, const size_t size) {
	qsort(aa, size, sizeof(*aa), cmp_int);
	for (int i = 0; i < (int)size; i++) {
		printf("0x%x\n", aa[i]);
	}
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);
	sort_str(ss, sizeof(ss)/sizeof(*ss));
	sort_str_2th(ss, sizeof(ss)/sizeof(*ss));
	sort_int(ii, sizeof(ii)/sizeof(*ii));
	return 0;
}
