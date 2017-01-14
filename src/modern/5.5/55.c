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

	uint16_t V=UINT16_MAX;
	uint16_t v_add_1=V+1;
	print_binary("V", V);
	print_binary("V+1", v_add_1);

	print_binary("A", a);
	print_binary("~A", ~a);
	print_binary("-A", -a);

	print_binary("~A=V-A", V-a);
	print_binary("-A=~A+1", ~a+1);

	print_binary("B", b);
	print_binary("A|B", a|b);
	print_binary("A&B", a&b);
	print_binary("A^B", a^b);


	print_binary("A^B=(A-(A&B))+(B-(A&B))", (a-(a&b))+(b-(a&b)));
	print_binary("A|B=A+B-(A&B)", a+b-(a&b));

	return 0;
}


