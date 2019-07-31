#include <_algo_.h>


void
insertion_sort(void *base, size_t nel, size_t width,
							 int (*comp)(const void *lhs, const void *rhs)) {
	for (size_t j = 1; j < nel; j++) {
		long long i = j-1;
		while (i >= 0 && comp((char*)base+i*width, (char*)base+j*width) > 0) {
			swap((char*)base+(i+1)*width, (char*)base+i*width, width);
			i--;
		}
		swap((char*)base+(i+1)*width, (char*)base+j*width, width);
	}
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int a1[] = { 0x3, 0x5, 0x4, 0x1, 0x2 };
	printf("insertion sort+:\n----------\n");
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
	printf("insertion sort-:\n----------\n");
	insertion_sort(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);

	char *s1[] = { "block", "array", "digit", "floor", "cell" };
	printf("insertion sort+:\n----------\n");
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
	printf("insertion sort-:\n----------\n");
	insertion_sort(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), comp_str);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);

	return 0;
}
