#include "ndef.h"
#include <stdio.h>

#include "nbits.h"

#if defined(BIT8_SEP)
#  undef BIT8_SEP
#endif
#define BIT8_SEP  ","

#if defined(BIT16_SEP)
#  undef BIT16_SEP
#endif
#define BIT16_SEP "|"

#if defined(BIT32_SEP)
#  undef BIT32_SEP
#endif
#define BIT32_SEP "\n                         "

#if defined(BIT8_PRE)
#  undef BIT8_PRE
#endif
#define BIT8_PRE  "0b: "

#if defined(BIT8_SUF)
#  undef BIT8_SUF
#endif
#define BIT8_SUF  "\n"


int
main(int argc, char **argv) 
{
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
