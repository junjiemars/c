#include "_wasm_.h"
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE
int
ver(void) {
  return 0x11223344;
}

EMSCRIPTEN_KEEPALIVE
int*
double_elem(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] *= 2;
  }
  return arr;
}

int
cmp_str(const void *s1, const void *s2) {
	return strcmp(*(char* const*)s1, *(char* const*)s2);
}

EMSCRIPTEN_KEEPALIVE
void
sort_str(char **aa, const size_t size) {
	qsort(aa, size, sizeof(*aa), cmp_str);
}


#ifdef __cplusplus
} /* end of extern "C" */
#endif


#if !__EMSCRIPTEN__
#include <stdio.h>

static char *ss[] = {
	"a1 9 2 3 1",
	"g1 act car",
	"zo4 4 7",
	"ab1 off key dog",
	"a8 act zoo",
};

void
show_ss(const char *title, char **aa, const size_t size) {
	printf("%s ss\n----------\n", title);
  for (size_t i = 0; i < size; i++) {
		printf("%s\n", aa[i]);
	}
	printf("----------\n");
}

int
main(void) {
  printf("ver() = %i\n", ver());
  size_t n = sizeof(ss)/sizeof(*ss);
  sort_str(ss, n);
  show_ss("sorted 1th", ss, n);
  return 0;
}

#endif /* end of !__EMSCRIPTEN__ */
