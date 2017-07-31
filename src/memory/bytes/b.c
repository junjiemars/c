#include <_memory_.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void 
basic_types() {
	uint8_t  x1 = 'A';
	printf("uint8_t: %c \t\t= #b"BIT_FMT_8"\n", x1, BIT_8(x1));

	uint8_t x1s = (uint8_t)-65;
	printf("uint8_t-: -%c \t\t= #b"BIT_FMT_8"\n", x1, BIT_8(x1s));

	uint16_t x2 = 'A';
	printf("uint16_t: %"PRIu16" \t\t= #b"BIT_FMT_16"\n", x2, BIT_16(x2));

	uint16_t x2s = (uint16_t)-65;
	printf("uint16_t-: %"PRIu16" \t= #b"BIT_FMT_16"\n", x2s, BIT_16(x2s));

	uint32_t x4 = 'A';
	printf("uint32_t: %"PRIu32" \t\t= #b"BIT_FMT_32"\n", x4, BIT_32(x4));

	uint64_t x8 = 'A';
	printf("uint64_t: %"PRIu64" \t\t= #b"BIT_FMT_64"\n", x8, BIT_64(x8));

	ufloat32_t x4f = { .f = 65.0f };
	printf("float: %f \t= #b"BIT_FMT_32"\n", x4f.f, BIT_32(x4f.u));

	ufloat32_t x4fs = { .f = -65.0f };
	printf("float-: %f \t= #b"BIT_FMT_32"\n", x4fs.f, BIT_32(x4fs.u));

	ufloat64_t x8f = { .f = 65.0l };
	printf("double: %lf \t= #b"BIT_FMT_64"\n", x8f.f, BIT_64(x8f.u));

	ufloat64_t x8fs = { .f = -65.0l };
	printf("double-: %lf \t= #b"BIT_FMT_64"\n", x8fs.f, BIT_64(x8fs.u));
}

void 
ieee_float() {
	ufloat32_t x4f =  { .f = 3.14f };
	printf("float: %f \t= #b"BIT_FMT_32"\n", x4f.f, BIT_32(x4f.u));

	ufloat32_t x4fs = { .f = -3.14f };
	printf("float: %f \t= #b"BIT_FMT_32"\n", x4fs.f, BIT_32(x4fs.u));

	printf("   sign     = #b"BIT_FMT_32"\n", BIT_32(x4fs.layout.sign));
	printf("   exponent = #b"BIT_FMT_32"\n", BIT_32(x4fs.layout.exponent));
	printf("   mantissa = #b"BIT_FMT_32"\n", BIT_32(x4fs.layout.mantissa));
}

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	
	printf("\nBASIC TYPES\n");
	printf("----------\n");
	basic_types();

	printf("\nIEEE FLOAT\n");
	printf("----------\n");
	ieee_float();
}
