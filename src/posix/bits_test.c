#include <nore.h>
#include <bits.h>
#include <stdio.h>

#define _unused_(x) ((void)(x))

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#ifdef BIT_PRE
#  undef  BIT_PRE
#  define BIT_PRE "2#"
#endif

	printf("0x%x: " BIT8_FMT "\n", 0x12, BIT8(0x12));
	printf("0x%x: " BIT16_FMT "\n", 0x1234, BIT16(0x1234));
	
	return 0;
}
