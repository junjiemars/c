#include <_algo_.h>
#include <stdio.h>
#include <assert.h>

void
bubble_sort(void *base, size_t nel, size_t width,
						int (*comp)(const void *, const void *)) {
	for (size_t i = 0; i < nel; i++) {
		for (size_t j = 0; j < nel - i - 1; j++) {
			if (comp((char*)base+j*width, (char*)base+(j+1)*width) > 0) {
				swap((char*)base+j*width, (char*)base+(j+1)*width, width);
			}
		}
	}
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int a1[] = { 0x3, 0x5, 0x1, 0x4, 0x1, 0x2 };
	printf("bubble sort+:\n----------\n");
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
	printf("bubble sort-:\n----------\n");
	bubble_sort(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);

	char *s1[] = { "block", "array", "floor", "digit", "floor", "cell", "cell" };
	printf("bubble sort+:\n----------\n");
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
	printf("bubble sort-:\n----------\n");
	bubble_sort(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), comp_str);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);

	return 0;
}
