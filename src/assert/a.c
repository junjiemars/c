#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define _unused_(x) (void)(x)

uint32_t
sqr(uint32_t x) {
	assert((0 < x) && (x < 100));
	return (x * x);
}

int
main(int argc, const char* argv[]) {
	if (argc <= 1) {
		printf("%s usage:\n\t <uint32_t>", argv[0]);
		return 0;
	}
	
	uint32_t n = (uint32_t)atoi(argv[1]);
	printf("sqr(%u)=%u\n", 2u, sqr(n));

	return 0;
}
