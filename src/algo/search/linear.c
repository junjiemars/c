#include <_algo_.h>

long
linear_search(void *what, void *base, size_t nel, size_t width,
							int (*comp)(const void *, const void *)) {
	assert(0 != what && "argument:what should not be null");
	assert(0 != base && "argument:base should not be null");
	assert(0 != comp && "argument:comp should not be null");
	if (0 == what || 0 == base || 0 == comp) {
		return -1;
	}
	for (size_t i = 0; i < nel; i++) {
		if (0 == comp((char*)what, (char*)base + i * width)) {
			return (long)i;
			break;
		}
	}
	return -2;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int found;
	int a1[] = { 0x3, 0x5, 0x4, 0x1, 0x2 };
	int what = 0x1;
	printf("linear search for %i\n----------\n", what);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = linear_search(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), comp_int);
	printf("found: [%i]\n", found);

	char *s1[] = { "a", "ccc", "bb", "dddd" };
	char *ss1 = "dddd";
	printf("linear search for %s\n----------\n", ss1);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = linear_search(&ss1, s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), comp_str);
	printf("found: [%i]\n", found);

	return 0;
}
