#include <_memory_.h>
#include <string.h>
#include <stdio.h>

typedef union u_bitfield {
	uint32_t val32;
	uint8_t val8[sizeof(uint32_t)/sizeof(uint8_t)];
	struct s_bifield {
#if (1 == NM_HAVE_LITTLE_ENDIAN)
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
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	u_bitfield u;
	memset(&u, 0, sizeof(u));

	u.fields.a = 1;
	u.fields.b = 2;
	u.fields.c = 3;
	u.fields.d = 4;

	printf("u_bitfield.val32 = 0x%x\n", u.val32);
	printf("u_bitfield.val8 =  0x%x 0x%x\n", u.val8[0], u.val8[1]);
}
