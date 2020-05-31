#include <_memory_.h>
#include <stdio.h>
#include <float.h>

#ifdef BIT8_SEP
#  undef  BIT8_SEP
#  define BIT8_SEP " "
#endif

#ifdef BIT16_SEP
#  undef  BIT16_SEP
#  define BIT16_SEP " "
#endif

#ifdef BIT32_SEP
#  undef  BIT32_SEP
#  define BIT32_SEP " "
#endif


void 
int_types() {
	uint8_t  x1 = 'A';
	printf("uint8_t:   %8c  =  " BIT8_FMT "\n", x1, BIT8(x1));

	uint8_t x1s = (uint8_t)(~x1 + 1);
	printf("uint8_t-:  %8c  =  " BIT8_FMT "\n", x1, BIT8(x1s));

	uint16_t x2 = 'A';
	printf("uint16_t:  %8"PRIu16"  =  " BIT16_FMT "\n", x2, BIT16(x2));

	uint16_t x2s = (uint16_t)(~x2 + 1);
	printf("uint16_t-: %8"PRIu16"  =  " BIT16_FMT "\n", x2, BIT16(x2s));

	uint32_t x4 = 'A';
	printf("uint32_t:  %8"PRIu32"  =  " BIT32_FMT "\n", x4, BIT32(x4));

	uint64_t x8 = 'A';
	printf("uint64_t:  %8"PRIu64"  =  " BIT64_FMT "\n", x8, BIT64(x8));
}

void
float_types() {
	ufloat32_t x0f = { .f = 0.0f };
	printf("float: %16f  =  " BIT32_FMT "\n", x0f.f, BIT32(x0f.u));

	ufloat32_t x4f = { .f = 65.0f };
	printf("float: %16f  =  " BIT32_FMT "\n", x4f.f, BIT32(x4f.u));

	ufloat32_t x4fs = { .f = -65.0f };
	printf("float: %16f  =  " BIT32_FMT "\n", x4fs.f, BIT32(x4fs.u));

	ufloat64_t x8f = { .f = 65.0l };
	printf("double:%16lf  =  " BIT64_FMT "\n", x8f.f, BIT64(x8f.u));

	ufloat64_t x8fs = { .f = -65.0l };
	printf("double:%16lf  =  " BIT64_FMT "\n", x8fs.f, BIT64(x8fs.u));
}

void 
ieee_float() {
	ufloat32_t x4f2 =  { .f = 2.0f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f2.f, BIT32(x4f2.u));

	ufloat32_t x4f2n = { .f = -2.0f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f2n.f, BIT32(x4f2n.u));

	printf("  sign     =  " BIT32_FMT "\n", BIT32(x4f2n.layout.sign));
	printf("  exponent =  " BIT32_FMT "\n", BIT32(x4f2n.layout.exponent));
	printf("  mantissa =  " BIT32_FMT "\n", BIT32(x4f2n.layout.mantissa));

	ufloat32_t x4f4 = { .f = 4.0f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f4.f, BIT32(x4f4.u));

	ufloat32_t x4f6 = { .f = 6.0f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f6.f, BIT32(x4f6.u));

	ufloat32_t x4f1 = { .f = 1.0f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f1.f, BIT32(x4f1.u));

	ufloat32_t x4f075 = { .f = 0.75f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f075.f, BIT32(x4f075.u));

	ufloat32_t x4f25 = { .f = 2.5f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f25.f, BIT32(x4f25.u));

	ufloat32_t x4f01 = { .f = 0.1f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f01.f, BIT32(x4f01.u));
}

void
ieee_float_special_values(void) {
  ufloat32_t x4f0 =  { .f = 0.f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f0.f, BIT32(x4f0.u));

  ufloat32_t x4f0n =  { .f = -0.f };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4f0n.f, BIT32(x4f0n.u));

  ufloat32_t x4finf =  { .f = (1.0f/0.0f) };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4finf.f, BIT32(x4finf.u));

  ufloat32_t x4finfn =  { .f = (-1.0f/0.0f) };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4finfn.f, BIT32(x4finfn.u));

  ufloat32_t x4fnan =  { .f = (0.0f/0.0f) };
	printf("float: %16f \t=  " BIT32_FMT "\n", x4fnan.f, BIT32(x4fnan.u));
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
