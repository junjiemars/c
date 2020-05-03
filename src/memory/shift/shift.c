#include <_memory_.h>
#include <stdio.h>


void unsigned_left_shift() {
  uint16_t x2 = 0x1122;
  printf("uint16_t: %" PRIu16 "      =  " BIT_FMT_16 "\n", x2, BIT_16(x2));
  printf("uint16_t: %" PRIu16 " << 2 =  " BIT_FMT_16 "\n", x2, BIT_16(x2 << 2));
}

void unsigned_right_shift() {
  uint16_t x2 = 0x1122;
  printf("uint16_t: %" PRIu16 "      =  " BIT_FMT_16 "\n", x2, BIT_16(x2));
  printf("uint16_t: %" PRIu16 " >> 2 =  " BIT_FMT_16 "\n", x2, BIT_16(x2 >> 2));
}

void signed_left_shift() {
  int16_t x2s = -0x0002;
  printf("int16_t: %" PRIi16 "      =  " BIT_FMT_16 "\n", x2s, BIT_16((uint16_t)x2s));
  printf("int16_t: %" PRIi16 " << 2 =  " BIT_FMT_16 "\n", x2s, BIT_16((uint16_t)(x2s << 2)));
}

void signed_right_shift() {
  int16_t x2s = -0x0002;
  printf("int16_t: %" PRIi16 "      =  " BIT_FMT_16 "\n", x2s, BIT_16((uint16_t)x2s));
  printf("int16_t: %" PRIi16 " >> 2 =  " BIT_FMT_16 "\n", x2s, BIT_16((uint16_t)(x2s >> 2)));
} 

void math() {
  uint16_t u = 2;
	printf("u << x == u * 2^x    => %s\n", _bool_((u << 2) == (u * 4)) );
  printf("u >> x == u * 2^(-x) => %s\n", _bool_((u >> 2) == (u / 4)) );

  int16_t i = 2;
  printf("i << x == i * 2^x    => %s\n", _bool_((i << 2) == (i * 4)) );
  printf("i >> x == (unsigned)i >> x | ~(~0u >> x) => %s\n",
				 _bool_((i >> 2) == (int16_t)(((uint16_t)i >> 2) | ~(~0u >> 2))) );

	printf("-x == ~x + 1         => %s\n", _bool_(-i == (~i + 1)) );	
}


int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\n*%s ENDIAN*\n", NM_CPU_LITTLE_ENDIAN ? "LITTLE" : "BIG");
	printf("----------\n");

	printf("\nUNSIGNED LEFT SHIFT\n");
	printf("----------\n");
  unsigned_left_shift();

	printf("\nUNSIGNED RIGHT SHIFT\n");
	printf("----------\n");
  unsigned_right_shift();

	printf("\nSIGNED LEFT SHIFT\n");
	printf("----------\n");
  signed_left_shift();

	printf("\nSIGNED RIGHT SHIFT\n");
	printf("----------\n");
  signed_right_shift();

	printf("\nMATH of SHIFT\n");
	printf("----------\n");
  math();

}
