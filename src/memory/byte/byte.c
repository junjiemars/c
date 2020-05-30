#include <_memory_.h>
#include <stdio.h>
#include <float.h>

void 
int_types() {
	uint8_t  x1 = 'A';
	printf("uint8_t:   %8c  =  " BIT_FMT_8 "\n", x1, BIT_8(x1));

	uint8_t x1s = (uint8_t)(~x1 + 1);
	printf("uint8_t-:  %8c  =  " BIT_FMT_8 "\n", x1, BIT_8(x1s));

	uint16_t x2 = 'A';
	printf("uint16_t:  %8"PRIu16"  =  " BIT_FMT_16 "\n", x2, BIT_16(x2));

	uint16_t x2s = (uint16_t)(~x2 + 1);
	printf("uint16_t-: %8"PRIu16"  =  " BIT_FMT_16 "\n", x2, BIT_16(x2s));

	uint32_t x4 = 'A';
	printf("uint32_t:  %8"PRIu32"  =  " BIT_FMT_32 "\n", x4, BIT_32(x4));

	uint64_t x8 = 'A';
	printf("uint64_t:  %8"PRIu64"  =  " BIT_FMT_64 "\n", x8, BIT_64(x8));
}

void
float_types() {
	ufloat32_t x0f = { .f = 0.0f };
	printf("float: %16f  =  " BIT_FMT_32 "\n", x0f.f, BIT_32(x0f.u));

	ufloat32_t x4f = { .f = 65.0f };
	printf("float: %16f  =  " BIT_FMT_32 "\n", x4f.f, BIT_32(x4f.u));

	ufloat32_t x4fs = { .f = -65.0f };
	printf("float: %16f  =  " BIT_FMT_32 "\n", x4fs.f, BIT_32(x4fs.u));

	ufloat64_t x8f = { .f = 65.0l };
	printf("double:%16lf  =  " BIT_FMT_64 "\n", x8f.f, BIT_64(x8f.u));

	ufloat64_t x8fs = { .f = -65.0l };
	printf("double:%16lf  =  " BIT_FMT_64 "\n", x8fs.f, BIT_64(x8fs.u));
}

void 
ieee_float() {
	ufloat32_t x4f2 =  { .f = 2.0f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f2.f, BIT_32(x4f2.u));

	ufloat32_t x4f2n = { .f = -2.0f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f2n.f, BIT_32(x4f2n.u));

	printf("  sign     =  " BIT_FMT_32 "\n", BIT_32(x4f2n.layout.sign));
	printf("  exponent =  " BIT_FMT_32 "\n", BIT_32(x4f2n.layout.exponent));
	printf("  mantissa =  " BIT_FMT_32 "\n", BIT_32(x4f2n.layout.mantissa));

	ufloat32_t x4f4 = { .f = 4.0f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f4.f, BIT_32(x4f4.u));

	ufloat32_t x4f6 = { .f = 6.0f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f6.f, BIT_32(x4f6.u));

	ufloat32_t x4f1 = { .f = 1.0f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f1.f, BIT_32(x4f1.u));

	ufloat32_t x4f075 = { .f = 0.75f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f075.f, BIT_32(x4f075.u));

	ufloat32_t x4f25 = { .f = 2.5f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f25.f, BIT_32(x4f25.u));

	ufloat32_t x4f01 = { .f = 0.1f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f01.f, BIT_32(x4f01.u));
}

void
ieee_float_special_values(void) {
  ufloat32_t x4f0 =  { .f = 0.f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f0.f, BIT_32(x4f0.u));

  ufloat32_t x4f0n =  { .f = -0.f };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4f0n.f, BIT_32(x4f0n.u));

  ufloat32_t x4finf =  { .f = (1.0f/0.0f) };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4finf.f, BIT_32(x4finf.u));

  ufloat32_t x4finfn =  { .f = (-1.0f/0.0f) };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4finfn.f, BIT_32(x4finfn.u));

  ufloat32_t x4fnan =  { .f = (0.0f/0.0f) };
	printf("float: %16f \t=  " BIT_FMT_32 "\n", x4fnan.f, BIT_32(x4fnan.u));
}

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	
	printf("\n*%s ENDIAN*\n", NM_CPU_LITTLE_ENDIAN ? "LITTLE" : "BIG");
	printf("----------\n");

	printf("\nINT TYPES\n");
	printf("----------\n");
	int_types();

  printf("\nFLOAT TYPES\n");
	printf("----------\n");
	float_types();

	printf("\nIEEE FLOAT\n");
	printf("----------\n");
	ieee_float();

	printf("\nIEEE FLOAT SPECIAL VALUES\n");
	printf("----------\n");
	ieee_float_special_values();
  
}
