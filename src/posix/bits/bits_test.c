#include <nore.h>
#include "bits.h"
#include <stdio.h>

#if !defined(_unused_)
#  define _unused_(x) ((void)(x))
#endif

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
  
#if defined(NM_CPU_CACHE_LINE) && (NM_CPU_CACHE_LINE == 64)
  printf("0x%lx: " BIT64_FMT "\n",
         0x1234567890abcdef, BIT64(0x1234567890abcdef));
#endif
	
	return 0;
}
