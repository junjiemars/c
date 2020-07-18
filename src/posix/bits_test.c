#include "nore.h"
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

  printf("%#18x = ", 0x12);
  printf(BPRI8(0x12));

  printf("%#18x = ", 0x1234);
  printf(BPRI16(0x1234));

  printf("%#18x = ", 0x12345678);
  printf(BPRI32(0x12345678));

#if (NM_CPU_CACHE_LINE == 64)
  printf("0x%16lx = ", 0x1234567890abcdef);
  printf(BPRI64(0x1234567890abcdef));
#endif
  
  return 0;
}
