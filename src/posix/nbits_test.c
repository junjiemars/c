#include <inttypes.h>
#include <stdio.h>
#include <nore.h>
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
main(void)
{
  printf("%#18" PRIx8 " = " BPRI8, (uint8_t) 0x12, BIT8(0x12));

  printf("%#18" PRIx16 " = " BPRI16, (uint16_t) 0x1234, BIT16(0x1234));

  printf("%#18" PRIx32 " = " BPRI32, (uint32_t) 0x12345678, BIT32(0x12345678));


#if (NM_CPU_CACHE_LINE) && (NM_CPU_CACHE_LINE == 64)
  printf("0x%16" PRIx64 " = " BPRI64, (uint64_t) 0x1234567890abcdef,
         BIT64(0x1234567890abcdef));
#endif

  return 0;
}
