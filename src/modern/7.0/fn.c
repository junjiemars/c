#include <modern.h>

/* simple recursion */
size_t gcd_0(size_t a, size_t b) {
	if (!a) return b;

	if (a < b) {
		return gcd_0(b % a, a);
	} else {
		return gcd_0(b, a);
	}
}

/* loop */
size_t gcd_1(size_t a, size_t b) {
	size_t c = a % b;
	while (0 != c) {
		a = b;
		b = c;
		c = a % b;
	}

	return b;
}

/* tail recursion */
size_t gcd_2_iter(size_t a, size_t b) {
	if (!a) return b;
	return gcd_2_iter(b % a, a);	
}

size_t gcd_2(size_t a, size_t b) {
	if (a < b) 
		return gcd_2_iter(a, b);
	else
		return gcd_2_iter(b, a);
}

int main(int argc, const char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("gcd_0(30, 18)=%lu\n", gcd_0(30, 18));
	printf("gcd_1(30, 18)=%lu\n", gcd_1(30, 18));
	printf("gcd_2(30, 18)=%lu\n", gcd_2(30, 18));

	return	0;
}
