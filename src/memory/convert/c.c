#include <_memory_.h>
#include <stdio.h>


void
char_short() {
	char c = 'A';
	short s = c;

  printf("char: %" PRIu8 " \t\t =  " BIT_FMT_8 "\n", c, BIT_8(c));
	printf("char -> short: %" PRIu16 "\t =  " BIT_FMT_16 "\n", s, BIT_16(s));

	s = (2<<7) + 1;
	c = s;
	printf("short: %" PRIu16 "\t\t =  " BIT_FMT_16 "\n", s, BIT_16(s));
  printf("short -> char: %" PRIu8 " \t =  " BIT_FMT_8 "\n", c, BIT_8(c));
}

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\n*%s ENDIAN*\n", NM_HAVE_LITTLE_ENDIAN ? "LITTLE" : "BIG");
	printf("----------\n");
	char_short();
}
