#include <_memory_.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t
bit_swap32(uint32_t x) {
	uint32_t b = 0;
	b |= (x & 0x000000ff) << 24;
	b |= (x & 0x0000ff00) << 8;
	b |= (x & 0x00ff0000) >> 8;
	b |= (x & 0xff000000) >> 24;
	return b;
}

uint16_t
bit_swap16(uint16_t x) {
	uint16_t b = 0;
	b |= (x & 0x00ff) << 8;
	b |= (x & 0xff00) >> 8;
	return b;
}

void
swap() {
	uint16_t u16 = 0x1122;
	uint32_t u32 = 0x11223344;
	
  printf("uint16_t: 0x%" PRIx16 " \t => 0x%" PRIx16 "\n", 
		u16, bit_swap16(u16));
	
  printf("uint32_t: 0x%" PRIx32 " \t => 0x%" PRIx32 "\n", 
		u32, bit_swap32(u32));
}


int
main(int argc, char *argv[]) {
  _unused_(argc);
  _unused_(argv);

  printf("\nlittle endian: %s\n", _bool_(NM_CPU_LITTLE_ENDIAN));
	printf("----------\n");

	swap();
}
