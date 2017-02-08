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
	const size_t l = *((const size_t*)x);
	const size_t r = *((const size_t*)y);

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
	printf("sizeof(char*)=%zu bytes\n", sizeof(char*));
	printf("sizeof(short*)=%zu bytes\n", sizeof(short*));
	printf("sizeof(int*)=%zu bytes\n", sizeof(int*));
	printf("sizeof(long*)=%zu bytes\n", sizeof(long*));
	printf("sizeof(float*)=%zu bytes\n", sizeof(float*));
	printf("sizeof(double*)=%zu bytes\n", sizeof(double*));
	printf("sizeof(uint64_t*)=%zu bytes\n", sizeof(uint64_t*));

	printf("----------\n");
	int v1 = 0x11223344, v2 = 0x44332211;
	const int* p1 = &v1;
	*(int**)&p1 = &v2;
	printf("<const int*>: p1=%d\n", *p1);

	int* const p2 = &v1;
	*(const int**)&p2 = &v2;
	printf("<int* const>: p2=%d\n", *p2);

	const int* const p3 = &v1;
	*(int**)&p3 = &v2;
	printf("<const int* const>: p3=%d\n", *p3);
	*(int**)&p3 = &v1;
	printf("<const int* const>: p3=%d\n", *p3);

	printf("----------\n");
	size_t a1[10] = { 0,1,2,3,4,5, };
	printf("sum(|sqr|)=%zu\n", sum(&sqr, a1, sizeof(a1)/sizeof(size_t)));

	printf("----------\n");
	char* ss1[] = { "a", "orange", "apple", "berry", NULL, };
	qsort(ss1, sizeof(ss1)/sizeof(char*)-1, sizeof(char*), &qs_s_cmp);
	for (char** p=ss1; *p != NULL; p++) {
		printf("%s ", p[0]);
	}
	putchar('\n');

	size_t rs1[10];
	size_t n_rs1 = sizeof(rs1)/sizeof(size_t);
	srand(time(0));
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
	

	return 0;
}
