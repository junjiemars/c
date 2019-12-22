#include <nore.h>
#include <bits.h>
#include <stdio.h>

#define _unused_(x) ((void)(x))

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#ifdef BIT8_PRE
#  undef  BIT8_PRE
#  define BIT8_PRE "2#"
#endif

	printf("0x%x: " BIT8_FMT "\n", 0x12, BIT8(0x12));
	printf("0x%x: " BIT16_FMT "\n", 0x1234, BIT16(0x1234));
	printf("0x%x: " BIT32_FMT "\n", 0x12345678, BIT32(0x12345678));
	
	return 0;
}
