#include <_mach_.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef union u_bitfield {
	uint16_t u16;
	uint8_t u8[sizeof(uint32_t)/sizeof(uint8_t)];
	struct s_bifield {
#if (1 == NM_CPU_LITTLE_ENDIAN)
		uint16_t d : 4;
		uint16_t c : 4;
		uint16_t b : 4;
		uint16_t a : 4;
#else
		uint16_t a : 4;
		uint16_t b : 4;
		uint16_t c : 4;
		uint16_t d : 4;
#endif
	} fields;
} u_bitfield;

int
main(void) {
	u_bitfield u;
	memset(&u, 0, sizeof(u));

	u.fields.a = 0x1;
	u.fields.b = 0x2;
	u.fields.c = 0x3;
	u.fields.d = 0b0100;

	printf("u_bitfield.u16 = 0x%x\n", u.u16);
	printf("u_bitfield.u8 =  0x%x 0x%x\n", u.u8[0], u.u8[1]);
}
