#include <modern.h>
#include <stdio.h>
#include <stdint.h>
/* #include <iso646.h> */

char* out_binary(uint16_t n, char* b16) {
  for (uint16_t i=(1 << (16-1)), j=0; i>0; i>>=1, ++j) {
    b16[j] = (n & i) ? '1' : '0';
  }
	return b16;
}

void print_binary(char* n, uint16_t v) {
	char b16[16+1];
	printf("----------\n%s=%u\n----------\n0x%04x\n", n, v, v);
	printf("%s\n", out_binary(v, b16));
}

int main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	uint16_t a=240;
	uint16_t b=287;

	print_binary("A", a);
	print_binary("~A", ~a);
	print_binary("-A", -a);
	print_binary("~A+1", ~a+1);

	print_binary("B", b);
	print_binary("A|B", a|b);
	print_binary("A&B", a&b);
	print_binary("A^B", a^b);

	return 0;
}


