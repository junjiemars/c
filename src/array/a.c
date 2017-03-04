#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define _unused_(x) ((void)(x))

#ifdef CC_MSVC
	#define M 3
	#define N 2
	#define Z 2
#else
	size_t M=3, N=2, Z=2;
#endif

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
#ifdef CC_MSVC
iter_aa(size_t m, size_t n, size_t a[M][N], size_t (*fn)(size_t), size_t r) {
#else
iter_aa(size_t m, size_t n, size_t a[m][n], size_t (*fn)(size_t), size_t r) {
#endif
	for (size_t i=0; i<m; ++i) {
		for (size_t j=0; j<n; ++j) {
			a[i][j] = (*fn)(r);
			printf("%4zu ", a[i][j]);
		}
		putchar('\n');
	}
}

void
iter_aa1(size_t m, size_t n, size_t* a, size_t (*fn)(size_t), size_t r) {
	for (size_t i=0; i<m; ++i) {
		for (size_t j=0; j<n; ++j) {
			a[i*n+j] = (*fn)(r);
			printf("%4zu ", a[i*n+j]);
		}
		putchar('\n');
	}
}

void 
iter_aaa1(size_t m, size_t n, size_t z, size_t* a, 
	size_t (*fn)(size_t), size_t r) {

	for (size_t i=0; i<m; ++i) {
		for (size_t j=0; j<n; ++j) {
			for (size_t k=0; k<z; ++k) {
				a[i*n*z+j*z+k] = (*fn)(r);
				printf("%4zu ", a[i*n*z+j*z+k]);
			}
			printf("|");
		}
		putchar('\n');
	}
}

void
fn1(size_t a[][N]) {
	assert(sizeof(*a) == sizeof(size_t) * N);
	_unused_(a);
}

void
fn2(int** a) {
	assert(sizeof(*a) == sizeof(int*));
	_unused_(a);
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

	printf("\n----------\n");
	printf("a0[1]=%i\n1[a0]=%i\n", a0[1], 1[a0]);

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
	srand((unsigned int)time(0));
	size_t aa1[M][N];
	printf("aa1<[%zu][%zu]/%zu>\n", M, N, sizeof(aa1)/sizeof(size_t));
	iter_aa(M, N, aa1, &randomize, 100);	

	printf("----------\n");
	size_t aa2[M*N];
	printf("aa2<[%zu*%zu]/%zu>\n", M, N, sizeof(aa2)/sizeof(size_t));
	iter_aa1(M, N, aa2, &randomize, 100);

	printf("----------\n");
	size_t aa3[M*N*Z];
	printf("aa2<[%zu*%zu*%zu]/%zu>\n", M, N, Z, sizeof(aa3)/sizeof(size_t));
	iter_aaa1(M, N, Z, aa3, &randomize, 100);

	size_t aa4[M][N];
	fn1(aa4);
		
	int* aa5[M];
	fn2(aa5);

	
	return 0;
}
