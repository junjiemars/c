#include <_algo_.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int *found;
	int a1[] = { 0x1, 0x2, 0x3, 0x4, 0x5 };
	int what = 0x4;
	printf("bsearch+:\n----------\n");
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
	printf("bsearch-:\n----------\n");
	found = bsearch(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	printf("bsearch found: [%i]\n", 0 == found ? -1 : *found);
	
	return 0;
}
