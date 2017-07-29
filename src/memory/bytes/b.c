#include <_memory_.h>
#include <stdio.h>
#include <stdint.h>

void basic_types() {
	uint8_t  x1 = 'A';
	printf("uint8_t: %c \t\t= #b"BIT_FMT_16"\n", x1, BIT_16(x1));

	uint16_t x2 = 'A';
	printf("uint16_t: %hu \t\t= #b"BIT_FMT_16"\n", x2, BIT_16(x2));

	uint32_t x4 = 'A';
	printf("uint32_t: %u \t\t= #b"BIT_FMT_32"\n", x4, BIT_32(x4));

	uint64_t x8 = 'A';
	printf("uint64_t: %llu \t\t= #b"BIT_FMT_64"\n", x8, BIT_64(x8));

	ufloat32_t x4f; x4f.f = 65.0f;
	printf("float: %f \t= #b"BIT_FMT_32"\n", x4f.f, BIT_32(x4f.u));

	ufloat64_t x8f; x8f.f = 65.0l;
	printf("double: %lf \t= #b"BIT_FMT_64"\n", x8f.f, BIT_64(x8f.u));
}

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	
	basic_types();
}
