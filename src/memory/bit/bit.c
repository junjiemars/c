#include <_memory_.h>
#include <stdio.h>

uint8_t
set_a_bit(uint8_t x, uint8_t n) {
	return x |= 1u << n;
}

int
main(void) {
	uint8_t x = 11;
	uint8_t z;
	
	printf("uint8_t: %" PRIu8 " = " BIT_FMT_8 "\n", x, BIT_8(x));
	z = set_a_bit(x, 2u);
	printf("set_a_bit(%" PRIu8 ", %u) = " BIT_FMT_8 "\n", x, 2u, BIT_8(z));
}

