#include <_memory_.h>
#include <stdio.h>

uint8_t
set_a_bit(uint8_t x, uint8_t n) {
	return x |= 1u << n;
}

uint8_t
clear_a_bit(uint8_t x, uint8_t n) {
	return x &= ~(1u << n);
}

uint8_t
toggle_a_bit(uint8_t x, uint8_t n) {
	return x ^= 1u << n;
}

uint8_t
change_a_bit(uint8_t x, uint8_t n, uint8_t v) {
	return x ^= (-!!v ^ x) & (1u << n);
}

int
main(void) {
	uint8_t x = 11;
	uint8_t z;
	
	printf("uint8_t: %" PRIu8 " = " BIT_FMT_8 "\n", x, BIT_8(x));

	printf("----------\n");
	z = set_a_bit(x, 2u);
	printf("set_a_bit(%" PRIu8 ", %u) = " BIT_FMT_8 "\n", x, 2u, BIT_8(z));

	printf("----------\n");
	z = clear_a_bit(x, 1u);
	printf("clear_a_bit(%" PRIu8 ", %u) = " BIT_FMT_8 "\n", x, 1u, BIT_8(z));
	printf("----------\n");
	z = toggle_a_bit(x, 2u);
	printf("toggle_a_bit(%" PRIu8 ", %u) = " BIT_FMT_8 "\n", x, 2u, BIT_8(z));
	printf("toggle_a_bit(%" PRIu8 ", %u) = " BIT_FMT_8 "\n", z, 2u, BIT_8(toggle_a_bit(z, 2u)));

	printf("----------\n");
	z = change_a_bit(x, 2u, 3u);
	printf("change_a_bit(%" PRIu8 ", %u, %u) = " BIT_FMT_8 "\n", x, 2u, 3u, BIT_8(z));
	z = change_a_bit(x, 2u, 0u);
	printf("change_a_bit(%" PRIu8 ", %u, %u) = " BIT_FMT_8 "\n", x, 2u, 0u, BIT_8(z));	
}

