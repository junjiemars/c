
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <nm_auto_config.h>
#include <nm_auto_header.h>


#define _unused_(x) (void)(x)

const char *BIT4[16] = {
	[ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
	[ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
	[ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
	[12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

#define BIT_SEP " "
#define BIT_FMT_8 "%s%s"
#define BIT_FMT_16 BIT_FMT_8 BIT_SEP BIT_FMT_8
#define BIT_FMT_32 BIT_FMT_16 BIT_SEP BIT_FMT_16
#define BIT_FMT_64 BIT_FMT_32 BIT_SEP BIT_FMT_32

#define BIT_8(n) BIT4[(n) >> 4], BIT4[(n) & 0x0f]
#define BIT_16(n) BIT_8((n) >> 8), BIT_8((n) & 0xff)
#define BIT_32(n) BIT_16((n) >> 16), BIT_16((n) & 0xffff)
#define BIT_64(n) BIT_32((n) >> 32), BIT_32((n) & 0xffffffff)


#ifdef NM_HAVE_STDINT_H
#include <stdint.h>
#else
#include <stddef.h>
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif


#endif /* end of _MEMORY_H_ */
