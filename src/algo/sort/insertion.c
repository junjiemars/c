#include <_algo_.h>


void
insertion_sort(void *base, size_t nel, size_t width,
							 int (*comp)(const void *lhs, const void *rhs)) {
	void *saved = malloc(width);
	for (size_t j = 1; j < nel; j++) {
		long long i = j-1;
		void *val = (char*)base+j*width;
		while (i >= 0 && comp((char*)base+i*width, val) > 0) {
			i--;
		}
		if ((long long)j == ++i/* important */) {
			continue;
		}
		memmove(saved, val, width);
		memmove((char*)base+(i+1)*width, (char*)base+i*width, (j-i)*width);
		memmove((char*)base+i*width, saved, width);
	}
	free(saved);
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
