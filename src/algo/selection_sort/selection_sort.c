#include <_algo_.h>
#include <stdio.h>
#include <string.h>

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
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int a1[] = { 0x3, 0x5, 0x4, 0x1, 0x2 };
	printf("selection sort+:\n----------\n");
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
	printf("selection sort-:\n----------\n");
	selection_sort(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);

	char *s1[] = { "block", "array", "digit", "floor", "cell" };
	printf("selection sort+:\n----------\n");
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
	printf("selection sort-:\n----------\n");
	selection_sort(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), comp_str);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
	
	return 0;
}
