#ifndef _NBITS_H_
#define _NBITS_H_


/* prefix */
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

/* suffix */
#if !defined(BIT8_SUF)
#  define BIT8_SUF  ""
#endif
#if !defined(BIT16_SUF)
#  define BIT16_SUF BIT8_SUF
#endif
#if !defined(BIT32_SUF)
#  define BIT32_SUF BIT16_SUF
#endif
#if !defined(BIT64_SUF)
#  define BIT64_SUF BIT32_SUF
#endif

/* seperator */
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

char const *BIT4[] = {
	[ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
	[ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
	[ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
	[12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

#define BIT8(n)  BIT4[(n) >> 4],   BIT4[(n)  & 0x0f]
#define BIT16(n) BIT8((n) >> 8),   BIT8((n)  & 0xff)
#define BIT32(n) BIT16((n) >> 16), BIT16((n) & 0xffff)
#define BIT64(n) BIT32((n) >> 32), BIT32((n) & 0xffffffff)

#define BPRI8  BIT8_PRE  BIT8_FMT  BIT8_SUF
#define BPRI16 BIT16_PRE BIT16_FMT BIT16_SUF
#define BPRI32 BIT32_PRE BIT32_FMT BIT32_SUF
#define BPRI64 BIT64_PRE BIT64_FMT BIT64_SUF


#endif /* end of _NBITS_H_ */
