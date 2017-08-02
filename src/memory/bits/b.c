#include <_memory_.h>
#include <stdint.h>
#include <stdio.h>


//void out(unsigned n) {
//  unsigned i;
//  printf("%16d: ", n);
//
//  for (i = 1 << (sizeof(unsigned)*8-1); i>0; i = i>>1) {
//    (n & i) ? printf("1") : printf("0");
//  }
//
//  printf("\n");
//}
//
//void out1(unsigned n) {
//  if (n > 1) out1(n/2);
//  printf("%d", n % 2);
//}

void unsigned_left_shift() {
  uint16_t x2 = 0x1122;
  printf("uint16_t: %"PRIu16" \t\t =  "BIT_FMT_16"\n", x2, BIT_16(x2));
  printf("uint16_t: %"PRIu16" << 2 \t =  "BIT_FMT_16"\n", x2, BIT_16(x2 << 2));
}

void unsigned_right_shift() {
  uint16_t x2 = 0x1122;
  printf("uint16_t: %"PRIu16" \t\t =  "BIT_FMT_16"\n", x2, BIT_16(x2));
  printf("uint16_t: %"PRIu16" >> 2 \t =  "BIT_FMT_16"\n", x2, BIT_16(x2 >> 2));
}

void signed_left_shift() {
  int16_t x2s = -0x1122;
  printf("int16_t: %"PRIi16" \t\t =  "BIT_FMT_16"\n", x2s, BIT_16((uint16_t)x2s));
  //printf("int16_t: %"PRIi16" << 2 \t =  "BIT_FMT_16"\n", x2s, BIT_16((uint16_t)x2s << 2));
}

void signed_right_shift() {
  int16_t x2s = -0x1122;
  printf("int16_t: %"PRIi16" \t\t =  "BIT_FMT_16"\n", x2s, BIT_16((uint16_t)x2s));
  printf("int16_t: %"PRIi16" >> 2 \t =  "BIT_FMT_16"\n", x2s, BIT_16((uint16_t)x2s >> 2));
} 


int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

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


  //out(7);
  //out(3L);

  //printf("%16d: ", 7); out1(7); printf("\n");
  //printf("%16d: ", 5); out1(5); printf("\n");

  //out(-3);

  //float f1 = 7.0, f2 = -7.0;
  //out(*(unsigned*)&f1);
  //out(*(unsigned*)&f2);

	//nt x = -94, y = 2;
	//nt ars = ((unsigned)x >> y | ~(~0u >> y));
	//ut(ars);

  //return 0;
}
