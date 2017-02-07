#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>

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

int
main(int argc, const char* argv[]) {
	
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
	

	return 0;
}
