#ifndef _BITS_H_
#define _BITS_H_

const char *BIT4[] = {
	[ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
	[ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
	[ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
	[12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

#if !defined(BIT8_PRE)
#  define BIT8_PRE  ""
#endif

#if !defined(BIT16_PRE)
#  define BIT16_PRE BIT8_PRE
#endif

#if !defined(BIT32_PRE)
#  define BIT32_PRE BIT16_PRE
#endif

#if !defined(BIT64_PRE)
#  define BIT64_PRE BIT32_PRE
#endif

#if !defined(BIT8_SEP)
#  define BIT8_SEP  " "
#endif

#if !defined(BIT16_SEP)
#  define BIT16_SEP BIT8_SEP
#endif

#if !defined(BIT32_SEP)
#  define BIT32_SEP BIT16_SEP
#endif

#define BIT8_FMT  "%s%s"
#define BIT16_FMT BIT8_FMT  BIT8_SEP  BIT8_FMT
#define BIT32_FMT BIT16_FMT BIT16_SEP BIT16_FMT
#define BIT64_FMT BIT32_FMT BIT32_SEP BIT32_FMT

#define BIT8(n)  BIT4[(n) >> 4],   BIT4[(n)  & 0x0f]
#define BIT16(n) BIT8((n) >> 8),   BIT8((n)  & 0xff)
#define BIT32(n) BIT16((n) >> 16), BIT16((n) & 0xffff)
#define BIT64(n) BIT32((n) >> 32), BIT32((n) & 0xffffffff)

#define BPRI8(x)  BIT8_PRE  BIT8_FMT  "\n", BIT8(x)
#define BPRI16(x) BIT16_PRE BIT16_FMT "\n", BIT16(x)
#define BPRI32(x) BIT32_PRE BIT32_FMT "\n", BIT32(x)
#define BPRI64(x) BIT64_PRE BIT64_FMT "\n", BIT64(x)


#endif /* end of _BITS_H_ */
