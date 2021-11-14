#include <_memory_.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define BIT8_SUF  "\n"
#include <nbits.h>

#define LOG8_1()    printf("%44s = ", "uint8_t")
#define LOG8_2(...) printf("%25s(%8"PRIu8",%8u) = ", __VA_ARGS__)
#define LOG8_3(...) printf("%16s(%8"PRIu8",%8u,%8u) = ", __VA_ARGS__);

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
	uint8_t x = 0xff;
	uint8_t z;

	printf("----------\n");
  LOG8_1();
  printf(BPRI8, BIT8(x));

	x = clear_a_bit(x, 1u);
  LOG8_2("clear_a_bit", x, 1u);
  printf(BPRI8, BIT8(x));

	x = clear_a_bit(x, 2u);
  LOG8_2("clear_a_bit", x, 2u);
  printf(BPRI8, BIT8(x));

	x = set_a_bit(x, 2u);
  LOG8_2("set_a_bit", x, 2u);
  printf(BPRI8, BIT8(x));

	x = set_a_bit(x, 1u);
  LOG8_2("set_a_bit", x, 1u);
  printf(BPRI8, BIT8(x));

	x = toggle_a_bit(x, 1u);
	LOG8_2("toggle_a_bit", x, 1u);
  printf(BPRI8, BIT8(x));

	x = toggle_a_bit(x, 1u);
	LOG8_2("toggle_a_bit", x, 1u);
  printf(BPRI8, BIT8(x));

	z = change_a_bit(x, 2u, 3u);
	LOG8_3("change_a_bit", x, 2u, 3u);
  printf(BPRI8, BIT8(z));

	z = change_a_bit(x, 2u, 0u);
	LOG8_3("change_a_bit", x, 2u, 0u);
  printf(BPRI8, BIT8(z));
}

