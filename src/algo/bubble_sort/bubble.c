#include <_algo_.h>
#include <stdlib.h>
#include <stdio.h>


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

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

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
