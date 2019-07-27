#include <_algo_.h>

#if MSVC
#  pragma warning(disable : 4267)
#endif

void *
binary_search(const void *what, void *base, size_t nel, size_t width,
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
		return binary_search(what, (char*)base + (mid + 1) * width, nel - mid - 1,
												 width, comp);
	}
	return 0;
}

void *
binary_search1(const void *what, void *base, size_t nel, size_t width,
							 int (*comp)(const void *lhs, const void *rhs)) {
	if (nel < 1) return 0;
	long l = 0, r = (long) (nel-1);
	while (l <= r) {
		long mid = l + (r-1)/2;
		long c = comp(what, (char*) base + mid*width);
		if (0 == c) {
			return (char*) base + mid*width;
		}
		if (0 > c) {
			r = mid-1+1; 
		} else {
			l = mid+1;
		}
	}
	return 0;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int *found1;
	int a1[] = { 0x1, 0x2, 0x3, 0x4, 0x5 };
	int what1 = 0x5;
	printf("binary search for %i\n----------\n", what1);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found1 = binary_search(&what1, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1),
												 comp_int);
	printf("found: %ld\n", (long)(0 == found1 ? -1 : found1 - a1));

	char *found2;
	char *s1[] = { "a", "bb", "ccc", "dddd", "eeeee" };
	char *what2 = "dddd";
	printf("binary search for %s\n----------\n", what2);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found2 = binary_search(&what2, s1, sizeof(s1)/sizeof(*s1), sizeof(*s1),
												 comp_str);
	printf("found: %ld\n", (long)(0 == found2 ? -1 : (char**)found2 - s1));

	// loop
	printf("binary search loop for %i\n----------\n", what1);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found1 = binary_search1(&what1, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1),
													comp_int);
	printf("found: %ld\n", (long)(0 == found1 ? -1 : found1 - a1));

	return 0;
}
