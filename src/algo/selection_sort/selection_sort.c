#include <_algo_.h>
#include <stdio.h>
#include <string.h>


int comp_int(const void *lhs, const void *rhs);

void
selection_sort(void *base, size_t nel, size_t width,
							 int (*comp)(const void *, const void *)) {
	for (size_t i = 0; i < nel; i++) {
		size_t min = i;
		for (size_t j = i+1; j < nel; j++) {
			if (comp((char*)base+min*width, (char*)base+j*width) > 0) {
				min = j;
			}
		}
		swap((char*)base+min*width, (char*)base+i*width, width);
	}
}

int
comp_int(const void *lhs, const void *rhs) {
	return *(const int*)lhs - *(const int*)rhs;
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
	printf("selection sort+:\n----------\n");
	list_int_array(a1, sizeof(a1)/sizeof(*a1));
	printf("selection sort-:\n----------\n");
	selection_sort(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	list_int_array(a1, sizeof(a1)/sizeof(*a1));

	
	return 0;
}
