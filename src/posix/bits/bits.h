#ifndef _BITS_H_
#define _BITS_H_


const char *BIT4[] = {
	[ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
	[ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
	[ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
	[12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};


#define BIT8_SEP " "
#define BIT8_PRE ""

#define BIT8_FMT  BIT8_PRE "%s%s"
#define BIT16_FMT BIT8_FMT BIT8_SEP BIT8_FMT
#define BIT32_FMT BIT16_FMT BIT8_SEP BIT16_FMT
#define BIT64_FMT BIT32_FMT BIT8_SEP BIT32_FMT

#define BIT8(n)  BIT4[(n) >> 4], BIT4[(n) & 0x0f]
#define BIT16(n) BIT8((n) >> 8), BIT8((n) & 0xff)
#define BIT32(n) BIT16((n) >> 16), BIT16((n) & 0xffff)
#define BIT64(n) BIT32((n) >> 32), BIT32((n) & 0xffffffff)


#endif /* end of _BITS_H_ */
