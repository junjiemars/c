/*
 * 1) negative integer presentation
 * 2) float presentation: (-1)+/- * 1.xxx * 2^(exp-2^7)
 * pattern: sign-bit(+/-) + exp(8) + significand(23)
 * 3) narrow to wide convertion
 * 4) wide to narrow convertion
 */

#include <stdio.h>

void print_in_binary(const char *prefix, unsigned n, int f) {
  size_t bytes = sizeof(unsigned);
  size_t bit_size = bytes*8-1;

  printf("%16s: ", prefix);
  
  for (unsigned i = 1<<bit_size, j = f; i>0; i = i>>1, j++) {
    if (1<<bit_size == i) {
      (n & i) ? printf("1 ") : printf("0 ");
      continue;
    }

    (n & i) ? printf("1") : printf("0");

    if (0 == j % 4) printf(" ");
    if (0 == j % 8) printf("| ");
    else if (1 == i) printf(" |");
  }
  
  printf("\n");
}

#define print_integer_in_binary(N) print_in_binary(#N" ", (N), 1)
#define print_float_in_binary(PREFIX, N) print_in_binary(#PREFIX" ", (N), 0)

int main(int argc, const char *argv[]) {
  print_integer_in_binary(-1);

  print_integer_in_binary(7);
  float f0 = 7;
  print_float_in_binary(7f, *(unsigned*)&f0);
  
  f0 = 12.375;
  print_float_in_binary(12.375f, *(unsigned*)&f0);

  f0 = -12.375;
  print_float_in_binary(-12.375f, *(unsigned*)&f0);

  float f1 = f0 + 12.375;
  print_float_in_binary(12.375-12.375, *(unsigned*)&f1);

  f1 = 0.0;
  print_float_in_binary(0f, *(unsigned*)&f1);
}
