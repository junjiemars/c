#include <stdio.h>

void out(unsigned n) {
  unsigned i;
  printf("%16d: ", n);

  for (i = 1 << (sizeof(unsigned)*8-1); i>0; i = i>>1) {
    (n & i) ? printf("1") : printf("0");
  }

  printf("\n");
}

void out1(unsigned n) {
  if (n > 1) out1(n/2);
  printf("%d", n % 2);
}

int main(int argc, const char *argv[]) {
  out(7);
  out(3L);

  printf("%16d: ", 7); out1(7); printf("\n");
  printf("%16d: ", 5); out1(5); printf("\n");

  out(-3);

  float f1 = 7.0, f2 = -7.0;
  out(*(unsigned*)&f1);
  out(*(unsigned*)&f2);

  return 0;
}
