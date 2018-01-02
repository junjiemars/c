#include <_memory_.h>
#include <stdio.h>


void
char_short() {
	int8_t c = 'A';
	int16_t s = c;

	printf("\nCHAR <=> SHORT\n");
	printf("----------\n");

  printf("char: %" PRIi8 " \t\t =  " BIT_FMT_8 "\n", c, BIT_8(c));
	printf("char -> short: %" PRIi16 "\t =  " BIT_FMT_16 "\n", s, BIT_16(s));

	s = 0xff + 4;
	printf("short: %" PRIi16 "\t\t =  " BIT_FMT_16 "\n", s, BIT_16(s));
#if defined (RISKY) && (RISKY) > 0
	c = s;
  printf("short -> char: %" PRIi8 " \t =  " BIT_FMT_8 "\n", c, BIT_8(c));
#endif


	c = -2;
	s = c;
  printf("char: %" PRIi8 "\t\t =  " BIT_FMT_8 "\n", c, BIT_8((uint8_t)c));
	printf("char -> short: %" PRIi16 "\t =  " BIT_FMT_16 "\n", s, BIT_16((uint16_t)s));

	s = 0xff01;
  printf("short: %" PRIi16 "\t\t =  " BIT_FMT_16 "\n", s, BIT_16((uint16_t)s));
#if defined (RISKY) && (RISKY) > 0
	c = s;
	printf("short -> char: %" PRIi8 "\t =  " BIT_FMT_8 "\n", c, BIT_8((uint8_t)c));
#endif
}

void
int_float() {
	uint32_t i = 5;

	printf("\nINT => FLOAT\n");
	printf("----------\n");

  printf("int: %" PRIu32 " \t\t\t =  " BIT_FMT_32 "\n", i, BIT_32(i));
	printf("int -> *(float*)&int: %f\n\t\t\t =  " BIT_FMT_32 "\n", 
		*(float*)&i, BIT_32(*(uint32_t*)&i));

#if defined (RISKY) && (RISKY) > 0
	float f = i;
	printf("int -> float: %f\n\t\t\t =  " BIT_FMT_32 "\n", f, BIT_32(*(uint32_t*)&f));
#endif
}

void 
float_short() {
	float f = 3.14159f;	

	printf("\nFLOAT => SHORT\n");
	printf("----------\n");

  printf("float: %f\n \t\t\t =  " BIT_FMT_32 "\n", f, BIT_32(*(uint32_t*)&f));
	printf("float -> *(short*)&float: %" PRIi16 "\n\t\t\t =  " BIT_FMT_16 "\n", 
		*(short*)&f, BIT_16(*(uint16_t*)&f));

#if defined (RISKY) && (RISKY) > 0
	int16_t s = f;
  printf("float -> short: %" PRIi16 "\n \t\t\t =  " BIT_FMT_16 "\n", 
		s, BIT_16(*(uint16_t*)&s));
#endif
}

void
math() {
	uint32_t u32 = 0xffff0102;

	printf("\nMATH of INT => SHORT\n");
	printf("----------\n");

	printf("*(short*)&int(x)  == int(x) & (~0u >> 8*sizeof(short)) \t\t=> %s\n", 
		_bool_(*(uint16_t*)&u32 == (u32 & (~0u >> 8*sizeof(uint16_t)))) );
}


int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	char_short();
	int_float();
	float_short();

	math();
}
