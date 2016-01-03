#include <stdio.h>

void print_binary(unsigned n) {
  unsigned i;
  for (i = 1 << (sizeof(unsigned)*8-1); i>0; i = i>>1) {
    (n & i) ? printf("1") : printf("0");
  }
  printf("\n");
}

void print_binary1(unsigned n) {
  if (n > 1) print_binary1(n/2);
  printf("%d", n % 2);
}

int main(int argc, const char *argv[]) {
  print_binary(7);
  print_binary(3L);

  print_binary1(7); printf("\n");
  print_binary1(5); printf("\n");

  print_binary(-3);

  float f = 7.0;
  print_binary(*(unsigned*)&f);
 }
