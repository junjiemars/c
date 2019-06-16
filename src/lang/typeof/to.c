#include <_lang_.h>
#include <stdio.h>

#if (NM_HAVE_TYPEOF)
#define swap(a, b)              \
	do {						              \
		typeof(a) _swap_temp_1 = a; \
		a = b;                      \
    b = _swap_temp_1;						\
	} while (0)
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int i1 = 0x1122, i2 = 0x3344;
	printf("before swap: i1 = 0x%x, i2 = 0x%x\n", i1, i2);
	swap(i1, i2);
	printf("after swap:  i1 = 0x%x, i2 = 0x%x\n", i1, i2);

	char *s1 = "abc", *s2 = "123";
	printf("before swap: s1 = %s, s2 = %s\n", s1, s2);
	swap(s1, s2);
	printf("after swap:  s1 = %s, s2 = %s\n", s1, s2);

	return 0;
}
