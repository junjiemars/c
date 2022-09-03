#include "_memory_.h"
#include <float.h>


#if defined(BIT8_SUF)
#  undef BIT8_SUF
#endif
#define BIT8_SUF  "\n"



typedef union
{
	float     f;
	uint32_t  u;
	struct
  {
		uint32_t sign:      1;      /* (u & 0x007fffff) */
		uint32_t exponent:  8;      /* ((u & 0x07800000) >> 23) */
		uint32_t mantissa: 23;      /* (u >> 31) */
	} layout;
} ufloat32_t;


int
main(int argc, char **argv)
{

}
