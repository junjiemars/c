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
	
	printf("uint8_t: %" PRIu8 " = " BIT8_FMT "\n", x, BIT8(x));

	printf("----------\n");
	z = set_a_bit(x, 2u);
	printf("set_a_bit(%" PRIu8 ", %u) = " BIT8_FMT "\n", x, 2u, BIT8(z));

	printf("----------\n");
	z = clear_a_bit(x, 1u);
	printf("clear_a_bit(%" PRIu8 ", %u) = " BIT8_FMT "\n", x, 1u, BIT8(z));
	printf("----------\n");
	z = toggle_a_bit(x, 2u);
	printf("toggle_a_bit(%" PRIu8 ", %u) = " BIT8_FMT "\n", x, 2u, BIT8(z));
	printf("toggle_a_bit(%" PRIu8 ", %u) = " BIT8_FMT "\n", z, 2u, BIT8(toggle_a_bit(z, 2u)));

	printf("----------\n");
	z = change_a_bit(x, 2u, 3u);
	printf("change_a_bit(%" PRIu8 ", %u, %u) = " BIT8_FMT "\n", x, 2u, 3u, BIT8(z));
	z = change_a_bit(x, 2u, 0u);
	printf("change_a_bit(%" PRIu8 ", %u, %u) = " BIT8_FMT "\n", x, 2u, 0u, BIT8(z));	
}

