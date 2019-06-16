#include <_algo_.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int comp_int(const void *lhs, const void *rhs);
void swap_int(void *lhs, void *rhs);

void
bubble_sort(void *base, size_t nel, size_t width,
						int (*comp)(const void *, const void *),
						void (*swap)(void *, void *)) {
	for (size_t i = 0; i < nel; i++) {
		for (size_t j = 1; j < nel - i - 1; j++) {
			if (comp((char*)base+i*width, (char*)base+j*width) > 0) {
				swap((char*)base+i*width, (char*)base+j*width);
			}
		}
	}
}

int
comp_int(const void *lhs, const void *rhs) {
	return *(const int*)lhs - *(const int*)rhs;
}

void
swap_int(void *lhs, void *rhs) {
	int t = *(int*)lhs;
	*(int*)lhs = *(int*)rhs;
	*(int*)rhs = t;
}

void
list_int_array(const int *a, size_t nel) {
	for (size_t i = 0; i < nel; i++) {
		printf("%i, ", a[i]);
	}
	printf("\n");
}

#if DEBUG
void
test_swap_int(void) {
	int i1 = 0x1122, i2 = 0x3344;
	swap_int((void*)&i1, (void*)&i2);
	assert(0x1122 == i2 && 0x3344 == i1);
	printf("test swap_int fn ... ok\n");
}

void
test_comp_int(void) {
	int i1 = 0x1122, i2 = 0x3344;
	int cmp = comp_int((void*)&i1, (void*)&i2);
	assert(cmp < 0 && "comp_int(0x1122, 0x3344) should < 0");
	cmp = comp_int((void*)&i1, (void*)&i1);
	assert(cmp == 0 && "comp_int(0x1122, 0x1122) should == 0");
	cmp = comp_int((void*)&i2, (void*)&i1);
	assert(cmp > 0 && "comp_int(0x3344, 0x1122) should > 0");
	printf("test cmp_int fn ... ok\n");
}
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#if DEBUG
	test_swap_int();
	test_comp_int();
#endif

	int a1[] = { 0x3, 0x5, 0x4, 0x1, 0x2 };
	printf("bubble sort+:\n----------\n");
	list_int_array(a1, sizeof(a1)/sizeof(*a1));
	printf("bubbel sort-:\n----------\n");
	bubble_sort(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1),
							comp_int,
							swap_int);
	list_int_array(a1, sizeof(a1)/sizeof(*a1));

	return 0;
}
