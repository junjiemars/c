#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define _unused_(x) ((void)(x))
void 
iter_a(int *a, size_t n) {
	for (size_t i=0; i<n; ++i) {
		printf("%d ", a[i]);
	}
	putchar('\n');
	
	int* p = a;
	while (n-- > 0) {
		printf("%d ", *p++);
	}
	putchar('\n');
}

size_t
randomize(size_t n) {
	size_t r = rand() % n;
	return r;
}

void
iter_aa(size_t m, size_t n, size_t a[m][n], size_t (*fn)(size_t), size_t r) {
	for (size_t i=0; i<m; ++i) {
		for (size_t j=0; j<n; ++j) {
			a[i][j] = (*fn)(r);
			printf("%4zu ", a[i][j]);
		}
		putchar('\n');
	}
}

int
main(int argc, const char* argv[]) {
	_unused_(argc);
	_unused_(argv);
	
	printf("----------\n");
	int a0[] = { 1, 10, 20 };
	printf("a0[3/%zu]\n", sizeof(a0)/sizeof(a0[0]));
	for (size_t i=0; i<sizeof(a0)/sizeof(int); ++i) {
		printf("%d ", a0[i]);
	}

	/* c99 */
	printf("\n----------\n");
	int a1[] = { [2]=20, [1]=10, [0]=1 };
	printf("a1[3/%zu]\n", sizeof(a1)/sizeof(int));
	for (size_t i=0; i<sizeof(a1)/sizeof(int); ++i) {
		printf("%d ", a1[i]);
	}

	printf("\n----------\n");
	int a2[5] = { [2]=20, [1]=10, [0]=1 };
	printf("a2[3/%zu]\n", sizeof(a2)/sizeof(int));
	for (size_t i=0; i<sizeof(a2)/sizeof(int); ++i) {
		printf("%d ", a2[i]);
	}

	printf("\n----------\n");
	printf("a2[3/%zu]\n", sizeof(a2)/sizeof(int));
	iter_a(a2, sizeof(a2)/sizeof(int));
	
	printf("----------\n");
	srand(time(0));
	size_t m=3, n=2;
	size_t aa1[m][n];
	printf("aa1<[%zu][%zu]/%zu]>\n", m, n, sizeof(aa1)/sizeof(size_t));
	iter_aa(m, n, aa1, &randomize, 100);	

	return 0;
}
