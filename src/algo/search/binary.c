#include <_algo_.h>

#if MSVC
#  pragma warning(disable : 4267)
#endif

void *
binary_search(void *what, void *base, size_t nel, size_t width,
							int (*comp)(const void*lhs, const void *rhs)) {
	assert(0 != what && "argument:what should not be null");
	assert(0 != base && "argument:base should not be null");
	assert(0 != comp && "argument:comp should not be null");

	if (1 <= nel) {
	  long mid = nel/2;
		long c = comp(what, (char*)base + mid * width);
		if (0 == c) {
			return (char*)base + mid * width;
		}
		if (0 > c) {
			return binary_search(what, base, (size_t)(mid - 1 + 1), width, comp);
		}
		return binary_search(what, (char*)base + (mid + 1) * width, nel - mid - 1, width, comp);
	}

	return 0;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int *found;
	int a1[] = { 0x1, 0x2, 0x3, 0x4, 0x5 };
	int what = 0x5;
	printf("binary search for %i\n----------\n", what);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = binary_search(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	printf("found: [%Ii]\n", 0 == found ? -1 : (found - a1));
	
	return 0;
}
