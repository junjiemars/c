#include <_memory_.h>
#include <stdio.h>


void
char_short() {
	int8_t c = 'A';
	int16_t s = c;

	printf("\nchar <=> short\n");
	printf("----------\n");

  printf("char: %" PRIu8 " \t\t =  " BIT_FMT_8 "\n", c, BIT_8(c));
	printf("char -> short: %" PRIu16 "\t =  " BIT_FMT_16 "\n", s, BIT_16(s));

	s = 0xff + 4;
	c = s;
	printf("short: %" PRIu16 "\t\t =  " BIT_FMT_16 "\n", s, BIT_16(s));
  printf("short -> char: %" PRIu8 " \t =  " BIT_FMT_8 "\n", c, BIT_8(c));

	c = -2;
	s = c;
  printf("char: %i\t\t =  " BIT_FMT_8 "\n", c, BIT_8((uint8_t)c));
	printf("char -> short: %i\t =  " BIT_FMT_16 "\n", s, BIT_16((uint16_t)s));

	s = 0xff01;
	c = s;
  printf("short: %i\t\t =  " BIT_FMT_16 "\n", s, BIT_16((uint16_t)s));
	printf("short -> char: %i\t =  " BIT_FMT_8 "\n", c, BIT_8((uint8_t)c));
}

void
int_float() {
	uint32_t i = 5;
	ufloat32_t f = { .u = i };

	printf("\nint => float\n");
	printf("----------\n");

  printf("int: %" PRIu32 " \t\t\t =  " BIT_FMT_32 "\n", i, BIT_32(i));
	printf("int -> float: %f\n\t\t\t =  " BIT_FMT_32 "\n", f.f, BIT_32(f.u));
	printf("int -> *(float*)&int: %f\n\t\t\t =  " BIT_FMT_32 "\n", 
		*(float*)&(f.u), BIT_32(*(uint32_t*)&f.f));
}

void 
float_short() {
	ufloat32_t f = { .f=3.14159f };
	uint16_t s = *(uint16_t*)&f.f;
	
	printf("\nfloat => short\n");
	printf("----------\n");

  printf("float: %f\n \t\t\t =  " BIT_FMT_32 "\n", f.f, BIT_32(f.u));
	printf("float -> *(short*)&float: %" PRIu16 "\n\t\t\t =  " BIT_FMT_16 "\n", 
		s, BIT_16(s));
}


int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\n*%s ENDIAN*\n", NM_HAVE_LITTLE_ENDIAN ? "LITTLE" : "BIG");
	printf("----------\n");

	char_short();
	int_float();
	float_short();
}
