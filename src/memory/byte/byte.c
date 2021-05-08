#include "_memory_.h"
#include <stdio.h>
#include <float.h>
#include "bits.h"
#include <inttypes.h>
#include <stdint.h>

typedef union {
	float f;
	uint32_t u;
	struct {
#if NM_CPU_LITTLE_ENDIAN
		uint32_t mantissa: 23; /* (u & 0x007fffff) */
		uint32_t exponent:  8; /* ((u & 0x07800000) >> 23) */
		uint32_t sign:      1; /* (u >> 31) */
#else
		uint32_t sign:      1;
		uint32_t exponent:  8;
		uint32_t manitssa: 23;
#endif
	} layout;
} ufloat32_t;

typedef union {
	double f;
	uint64_t u;
  struct {
#if NM_CPU_LITTLE_ENDIAN
    uint64_t mantissa: 52;
    uint64_t exponent: 11;
    uint64_t sign:      1;
#else
    uint64_t sign:      1;
    uint64_t exponent: 11;
    uint64_t mantissa: 52;
#endif
  } layout;
} ufloat64_t;

void int_types(void);
void float_types(void);
void ieee_float(void);
void ieee_float_special_values(void);
void ieee_double(void);

void 
int_types(void) {
	uint8_t  x1 = 'A';
	printf("uint8_t:   %8c  =  ", x1);
  printf(BPRI8(x1));

	uint8_t x1s = (uint8_t)(~x1 + 1);
	printf("uint8_t-:  %8c  =  ", x1);
  printf(BPRI8(x1s));

	uint16_t x2 = 'A';
	printf("uint16_t:  %8"PRIu16"  =  ", x2);
  printf(BPRI16(x2));

	uint16_t x2s = (uint16_t)(~x2 + 1);
	printf("uint16_t-: %8"PRIu16"  =  ", x2);
  printf(BPRI16(x2s));

	uint32_t x4 = 'A';
	printf("uint32_t:  %8"PRIu32"  =  ", x4);
  printf(BPRI32(x4));

	uint64_t x8 = 'A';
	printf("uint64_t:  %8"PRIu64"  =  ", x8);
  printf(BPRI64(x8));
}

void
float_types() {
	ufloat32_t x0f = { .f = 0.0f };
	printf("float: %16f  =  ", x0f.f);
  printf(BPRI32(x0f.u));

	ufloat32_t x4f = { .f = 65.0f };
	printf("float: %16f  =  ", x4f.f);
  printf(BPRI32(x4f.u));

	ufloat32_t x4fs = { .f = -65.0f };
	printf("float: %16f  =  ", x4fs.f);
  printf(BPRI32(x4fs.u));

	ufloat64_t x8f = { .f = 65.0 };
	printf("double:%16lf  =  ", x8f.f);
  printf(BPRI64(x8f.u));

	ufloat64_t x8fs = { .f = -65.0 };
	printf("double:%16lf  =  ", x8fs.f);
  printf(BPRI64(x8fs.u));
}

void 
ieee_float() {
  ufloat32_t x4f0 = { .f = 0.0f };
	printf("float: %16f \t=  ", x4f0.f);
  printf(BPRI32(x4f0.u));

	ufloat32_t x4f2 =  { .f = 2.0f };
	printf("float: %16f \t=  ", x4f2.f);
  printf(BPRI32(x4f2.u));

	ufloat32_t x4f2n = { .f = -2.0f };
	printf("float: %16f \t=  ", x4f2n.f);
  printf(BPRI32(x4f2n.u));

	printf("  sign     =  " BPRI32(x4f2n.layout.sign));
	printf("  exponent =  " BPRI32(x4f2n.layout.exponent));
	printf("  mantissa =  " BPRI32(x4f2n.layout.mantissa));

	ufloat32_t x4f4 = { .f = 4.0f };
	printf("float: %16f \t=  ", x4f4.f);
  printf(BPRI32(x4f4.u));

	ufloat32_t x4f8 = { .f = 8.0f };
	printf("float: %16f \t=  ", x4f8.f);
  printf(BPRI32(x4f8.u));

	ufloat32_t x4f6 = { .f = 6.0f };
	printf("float: %16f \t=  ", x4f6.f);
  printf(BPRI32(x4f6.u));

	ufloat32_t x4f7 = { .f = 7.0f };
	printf("float: %16f \t=  ", x4f7.f);
  printf(BPRI32(x4f7.u));

	ufloat32_t x4f1 = { .f = 1.0f };
	printf("float: %16f \t=  ", x4f1.f);
  printf(BPRI32(x4f1.u));

  ufloat32_t x4f05 = { .f = 0.5f };
	printf("float: %16f \t=  ", x4f05.f);
  printf(BPRI32(x4f05.u));

  ufloat32_t x4f025 = { .f = 0.25f };
	printf("float: %16f \t=  ", x4f025.f);
  printf(BPRI32(x4f025.u));

	ufloat32_t x4f075 = { .f = 0.75f };
	printf("float: %16f \t=  ", x4f075.f);
  printf(BPRI32(x4f075.u));

	ufloat32_t x4f205 = { .f = 2.5f };
	printf("float: %16f \t=  ", x4f205.f);
  printf(BPRI32(x4f205.u));

	ufloat32_t x4f01 = { .f = 0.1f };
	printf("float: %16f \t=  ", x4f01.f);
  printf(BPRI32(x4f01.u));
}

void
ieee_float_special_values(void) {
  ufloat32_t x4f0 =  { .f = 0.f };
	printf("float: %16f \t=  ", x4f0.f);
  printf(BPRI32(x4f0.u));

  ufloat32_t x4f0n =  { .f = -0.f };
	printf("float: %16f \t=  ", x4f0n.f);
  printf(BPRI32(x4f0n.u));

/* stupid msvc C2124: divide or mod by zero */
/* #if !(MSVC) */
  ufloat32_t x4finf =  { .f = (1.0f/0.0f) };
	printf("float: %16f \t=  ", x4finf.f);
  printf(BPRI32(x4finf.u));

  ufloat32_t x4finfn =  { .f = (-1.0f/0.0f) };
	printf("float: %16f \t=  ", x4finfn.f);
  printf(BPRI32(x4finfn.u));

  ufloat32_t x4fnan =  { .f = (0.0f/0.0f) };
	printf("float: %16f \t=  ", x4fnan.f);
  printf(BPRI32(x4fnan.u));
/* #endif */

  ufloat32_t x4fmin =  { .f = FLT_MIN };
	printf("float: %16s \t=  ", "min");
  printf(BPRI32(x4fmin.u));

  ufloat32_t x4fmax =  { .f = FLT_MAX };
	printf("float: %16s \t=  ", "max");
  printf(BPRI32(x4fmax.u));
}

void 
ieee_double() {
	ufloat64_t x8f2 =  { .f = 2.0 };
	printf("float: %16f \t=  ", x8f2.f);
  printf(BPRI64(x8f2.u));

	ufloat64_t x8f2n = { .f = -2.0 };
	printf("float: %16f \t=  ", x8f2n.f);
  printf(BPRI64(x8f2n.u));
  
	/* printf("  sign     =  " BPRI64(x8f2n.layout.sign)); */
	/* printf("  exponent =  " BPRI64(x8f2n.layout.exponent)); */
	/* printf("  mantissa =  " BPRI64(x8f2n.layout.mantissa)); */

	ufloat64_t x8f4 = { .f = 4.0 };
	printf("float: %16f \t=  ", x8f4.f);
  printf(BPRI64(x8f4.u));

	ufloat64_t x8f8 = { .f = 8.0 };
	printf("float: %16f \t=  ", x8f8.f);
  printf(BPRI64(x8f8.u));

	ufloat64_t x8f6 = { .f = 6.0 };
	printf("float: %16f \t=  ", x8f6.f);
  printf(BPRI64(x8f6.u));

	ufloat64_t x8f1 = { .f = 1.0 };
	printf("float: %16f \t=  ", x8f1.f);
  printf(BPRI64(x8f1.u));

	ufloat64_t x8f075 = { .f = 0.75 };
	printf("float: %16f \t=  ", x8f075.f);
  printf(BPRI64(x8f075.u));

	ufloat64_t x8f25 = { .f = 2.5 };
	printf("float: %16f \t=  ", x8f25.f);
  printf(BPRI64(x8f25.u));

	ufloat64_t x8f01 = { .f = 0.1 };
	printf("float: %16f \t=  ", x8f01.f);
  printf(BPRI64(x8f01.u));
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

	printf("\nIEEE DOUBLE\n");
	printf("----------\n");
	ieee_double();
  
}
