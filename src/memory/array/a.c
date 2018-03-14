#include <_memory_.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



#if MSVC 
	#pragma warning(disable:4706) /* strcpy4: assignment within conditional expression */
#elif GCC
	#pragma GCC diagnostic ignored "-Wparentheses"  /* strcp4: */
#elif CLANG
	#pragma clang diagnostic ignored "-Wparentheses"  /* strcp4: */
#endif


#ifdef MSVC
	#define M 3
	#define N 2
	#define Z 2
#else
	size_t M=3, N=2, Z=2;
#endif


#define _GAP_ 4

void 
bracket_syntax() {
	int a[] = { 1, 2, 3, };

	printf("\n[] OPERATOR\n");
	printf("----------\n");
	printf(" a[b] == *(a+b) \t=> \t%s\n", _bool_(a[1] == *(a+1)));
	printf("&a[b] == (a+b) \t\t=> \t%s\n", _bool_(&a[1] == (a+1)));
	printf(" a[b] == b[a] \t\t=> \t%s\n", _bool_(a[1] == 1[a]));
}

char *
strcpy1(char * dst, const char * src) {
	int i;

	for (i=0; src[i] != '\0'; i++) {
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return dst;	
}

char *
strcpy2(char * dst, const char * src) {
	int i = 0;
	
	while ((dst[i] = src[i]) != '\0') {
		i++;
	}
	return dst;
}

char *
strcpy3(char * dst, const char * src) {
	char * p = dst;

	while ((*p++ = *src++) != '\0') ;	
	return dst;
}

char * 
strcpy4(char * dst, const char * src) {
	char * p = dst;
	/* -Wparentheses: ./configure --has-memory --without-error */

	while ( *p++ = *src++ ) ;
	return dst;
}

void pointer_syntax() {
	printf("\nPOINTER++ SYNTAX\n");
	printf("----------\n");

	const char *ss = "strcpy foo++";
	int n = 12;

	char *s = malloc(n * sizeof s);
	printf("strcpy1: '%s' = '%s'\n", ss, strcpy1(s, ss));
	free(s);

	s = malloc(n * sizeof s);	
	printf("strcpy2: '%s' = '%s'\n", ss, strcpy2(s, ss));
	free(s);

	s = malloc(n * sizeof s);	
	printf("strcpy3: '%s' = '%s'\n", ss, strcpy3(s, ss));
	free(s);

	s = malloc(n * sizeof s);	
	printf("strcpy4: '%s' = '%s'\n", ss, strcpy4(s, ss));
	free(s);

}

void array_vs_pointer() {
	uint16_t head[_GAP_] = { 0 };
	uint16_t a[8];
	uint16_t tail[_GAP_] = { 0 };

	_unused_(head);
	_unused_(tail);

	printf("\nARRAY vs. POINTER\n");
	printf("----------\n");

	a[3] = 0xff00;
  printf("a[3|8]: 0x%x" PRIu16 " \t\t =  " BIT_FMT_16 "\n", a[3], BIT_16(a[3]));

	uint8_t *s = (uint8_t*)a + 6; // &((unt8_t*)a)[6]
	*s = 0x12;
  printf("((uint8_t*)a)[6]: 0x%x" PRIu8 " \t =  " BIT_FMT_8 "\n", *s, BIT_8((uint8_t)*s));
  printf("a[3]: 0x%x" PRIu16 " \t\t\t =  " BIT_FMT_16 "\n", a[3], BIT_16(a[3]));

	// dangerous

	*(a+8) = 0x4433;
  printf("a[9]: 0x%x" PRIu16 " \t\t\t =  " BIT_FMT_16 "\n", *(a+8), BIT_16(*(a+8)));

	a[0] = 0x4433;
  printf("a[0]: 0x%x" PRIu16 " \t\t\t =  " BIT_FMT_16 "\n", a[3], BIT_16(a[0]));
	*(a-1) = 0x1122;
  printf("a[-1]: 0x%x" PRIu16 " \t\t =  " BIT_FMT_16 "\n", *(a-1), BIT_16(*(a-1)));

  printf("a[-1,0]: 0x%x" PRIu32 " \t\t =  " BIT_FMT_32 "\n", 
		*(uint32_t*)(a-1), BIT_32(*(uint32_t*)(a-1)));
}

void dynamic_array() {
	printf("\nDYNAMIC ARRAY\n");
	printf("----------\n");

	int stack[100];
	printf("alloc on stack int[]: %zu\n", _sizeof_array_(stack));

	size_t l = 100;
	int *b = malloc(sizeof b * l);
	printf("alloc on heap int*: %zu\n", l);
	free(b);
}


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
#ifdef MSVC
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

	bracket_syntax();	
	pointer_syntax();

	array_vs_pointer();
	dynamic_array();

	//printf("----------\n");
	//int a0[] = { 1, 10, 20 };
	//printf("a0[3/%zu]\n", _array_size_(a0));
	//for (size_t i=0; i < _array_size_(a0); ++i) {
	//	printf("%d ", a0[i]);
	//}

	//printf("\n----------\n");
	//printf("a0[1]=%i\n1[a0]=%i\n", a0[1], 1[a0]);

	///* c99 */
	//printf("\n----------\n");
	//int a1[] = { [2]=20, [1]=10, [0]=1 };
	//printf("a1[3/%zu]\n", _array_size_(a1));
	//for (size_t i=0; i < _array_size_(a1); ++i) {
	//	printf("%d ", a1[i]);
	//}

	//printf("\n----------\n");
	//int a2[5] = { [2]=20, [1]=10, [0]=1 };
	//printf("a2[3/%zu]\n", _array_size_(a2));
	//for (size_t i=0; i < _array_size_(a2); ++i) {
	//	printf("%d ", a2[i]);
	//}

	//printf("\n----------\n");
	//printf("a2[3/%zu]\n", _array_size_(a2));
	//iter_a(a2, _array_size_(a2));
	//
	//printf("----------\n");
	//srand((unsigned int)time(0));
	//size_t aa1[M][N];
	//printf("aa1<[%zu][%zu]/%zu>\n", M, N, _array_size_(aa1));
	//iter_aa(M, N, aa1, &randomize, 100);	

	//printf("----------\n");
	//size_t aa2[M*N];
	//printf("aa2<[%zu*%zu]/%zu>\n", M, N, _array_size_(aa2));
	//iter_aa1(M, N, aa2, &randomize, 100);

	//printf("----------\n");
	//size_t aa3[M*N*Z];
	//printf("aa2<[%zu*%zu*%zu]/%zu>\n", M, N, Z, _array_size_(aa3));
	//iter_aaa1(M, N, Z, aa3, &randomize, 100);

	//size_t aa4[M][N];
	//fn1(aa4);
	//	
	//int* aa5[M];
	//fn2(aa5);

	
	return 0;
}
