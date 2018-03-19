#include <_lang_.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int
qs_s_cmp(const void* x, const void* y) {
	const char* l = *(const char**)x;
	const char* r = *(const char**)y;
	
	return strncmp(l, r, 10);
}

int
qs_i_cmp(const void* x, const void* y) {
	const size_t l = *(const size_t*)x;
	const size_t r = *(const size_t*)y;

	if (l < r) return -1;
	if (l > r) return 1;
	return 0;
}


int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

	printf("----------\n");
	char* ss1[] = { "a", "orange", "apple", "berry", NULL, };
	qsort(ss1, sizeof(ss1)/sizeof(ss1[0])-1, sizeof(ss1[0]), &qs_s_cmp);
	for (char** p=ss1; *p != NULL; p++) {
		printf("%s ", p[0]);
	}
	putchar('\n');

	size_t rs1[10];
	size_t n_rs1 = sizeof(rs1)/sizeof(rs1[0]);
	srand((unsigned int)time(0));
	for (size_t i=0; i<n_rs1; ++i) {
		rs1[i] = rand() % 100;
		printf("%zu ", rs1[i]);
	}
	putchar('\n');
	qsort(rs1, n_rs1, sizeof(size_t), &qs_i_cmp);
	for (size_t i=0; i<n_rs1; ++i) {
		printf("%zu ", rs1[i]);
	}
	putchar('\n');

	printf("----------\n");
	char *ss2[sizeof(ss1)/sizeof(char*)] = { 0 };
	for (size_t i=0; i<sizeof(ss1)/sizeof(char*)-1; ++i) {
		size_t n = 10;
		ss2[i] = malloc(n * sizeof(char));	
		memcpy(ss2[i], ss1[i], n);
	}	
	for (char** p=ss2; *p!=0; p++) {
		printf("%s ", *p);
	}
	putchar('\n');
	for (size_t i=0; i<sizeof(ss2)/sizeof(char*)-1; ++i) {
		free(ss2[i]);
	}
	
	printf("----------\n");
	char* *p_ss1 = ss1;
	/* point to array of char* */
	char* (*pa_ss1)[sizeof(ss1)/sizeof(ss1[0])] = &ss1;	
	printf("addressof(ss1[0])=%p\nchar** =%p\nchar* (*)[]=%p\n", ss1, p_ss1, pa_ss1);
	printf("&ss1[1]<%p>==(ss1+1)<%p>\n", &ss1[1], ss1+1);

}
