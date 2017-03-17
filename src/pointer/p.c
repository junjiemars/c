#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t 
sqr(size_t n) {
	return (n*n);
}

size_t
sum(size_t (*fn)(size_t), size_t* lst, size_t n) {
	size_t s = 0;
	for (size_t i=0; i<n; ++i) {
		s += (*fn)(lst[i]);
	}	
	return s;
}

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
main(){
	printf("----------\n");
	char* ss[] = { "first", "second", "third", NULL/*must has*/ };
	for (char** p=ss; *p != NULL; p++) {
		printf("%s ", p[0]);
	}
	printf("\naddress of the list is:%p\n", ss);

	printf("----------\n");
	printf("sizeof(void*)=%zu bytes\n", sizeof(void*));
	printf("sizeof(char*)=%zu bytes\n", sizeof(char*));
	printf("sizeof(short*)=%zu bytes\n", sizeof(short*));
	printf("sizeof(int*)=%zu bytes\n", sizeof(int*));
	printf("sizeof(long*)=%zu bytes\n", sizeof(long*));
	printf("sizeof(float*)=%zu bytes\n", sizeof(float*));
	printf("sizeof(double*)=%zu bytes\n", sizeof(double*));
	printf("sizeof(uint64_t*)=%zu bytes\n", sizeof(uint64_t*));

	printf("----------\n");
	int v1 = 0x11223344, v2 = 0x44332211;
	const int *p1 = &v1;
	**(int**)&p1 = v2+0x1;
	printf("<const int*>: p1<%p>=%d\n", p1, *p1);

	int *const p2 = &v1;
	*(int**)&p2 = &v2;
	printf("<int* const>: p2<%p>=%d\n", p2, *p2);

	const int *const p3 = &v1;
	*(int**)&p3 = &v2;
	printf("<const int* const>: p3<%p>=%d\n", p3, *p3);
	**(int**)&p3 = *p3+0x1;
	printf("<const int* const>: p3<%p>=%d\n", p3, *p3);

	int *p41 = &v1;
	int* *p4 = &p41;
	printf("<int**>: p4<%p>=%d\n", *p4, **p4);
	
	const int** p5 = &p1;
	printf("<const int**>: p5<%p>=%d\n", *p5, **p5);	

	int *const *p6 = &p2;
	printf("<int* const*>: p6<%p>=%d\n", *p6, **p6);

	int **const p7 = &p41;
	printf("<int** const>: p7<%p>=%d\n", *p7, **p7);

	const int *const *p8 = &p1;
	printf("<const int* const*>: p8<%p>=%d\n", *p8, **p8);

	const int **const p9 = &p1;
	printf("<const int** const>: p9<%p>=%d\n", *p9, **p9);

	int *const *const p0 = &p41;
	printf("<int* const* const>: p0<%p>=%d\n", *p0, **p0);
	

	printf("----------\n");
	size_t a1[10] = { 0,1,2,3,4,5, };
	printf("sum(|sqr|)=%zu\n", sum(&sqr, a1, sizeof(a1)/sizeof(a1[0])));

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

	return 0;
}
