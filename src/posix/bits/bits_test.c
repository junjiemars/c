#include "bits.h"
#include <stdio.h>

#ifdef BIT8_SEP
#  undef BIT8_SEP
#  define BIT8_SEP " "
#endif

#ifdef BIT16_SEP
#  undef BIT16_SEP
#  define BIT16_SEP " "
#endif

#ifdef BIT32_SEP
#  undef BIT32_SEP
#  define BIT32_SEP " "
#endif

#ifdef BIT8_PRE
#  undef BIT8_PRE
#  define BIT8_PRE " "
#endif

#ifdef BIT16_PRE
#  undef BIT16_PRE
#  define BIT16_PRE " "
#endif

#ifdef BIT32_PRE
#  undef BIT32_PRE
#  define BIT32_PRE " "
#endif

#ifdef BIT64_PRE
#  undef BIT64_PRE
#  define BIT64_PRE " "
#endif

#ifndef _unused_
#  define _unused_(x) ((void)(x))
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("%#18x = " BIT8_PRE BIT8_FMT "\n", 0x12, BIT8(0x12));
	printf("%#18x = " BIT16_PRE BIT16_FMT "\n", 0x1234, BIT16(0x1234));
	printf("%#18x = " BIT32_PRE BIT32_FMT "\n", 0x12345678, BIT32(0x12345678));
  
#if defined(NM_CPU_CACHE_LINE) && (NM_CPU_CACHE_LINE == 64)
  printf("0x%16lx = " BIT64_PRE BIT64_FMT "\n",
         0x1234567890abcdef, BIT64(0x1234567890abcdef));
#endif
	
	return 0;
}
