#include <modern.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	/* arithmetic overflow: wrapping around */
#ifdef DARWIN
	printf("SIZE_MAX=%llu\n", SIZE_MAX);
#else
	printf("SIZE_MAX=%zu\n", SIZE_MAX);
#endif
	size_t max = SIZE_MAX;
	printf("SIZE_MAX+1=%zu\n", max += 1);
	printf("SIZE_MAX+1-1=%zu\n", max -= 1);

	size_t a = 123;
	size_t b = 11;
	printf("a=(a/b)*b+a%%b when a=%zu b=%zu a/b=%zu a%%b=%zu\n", 
					a, b,
					a/b, a%b);
	printf("a%%b=a-(a/b)*b when a=%zu b=%zu a/b=%zu a%%b=%zu\n", 
					a, b,
					a/b, a%b);

	/* Arithmetic on size_t implicitly does computation % (SIZE_MAX+1) */

	return 0;
}
