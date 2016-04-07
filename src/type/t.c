#include <stdio.h>

int main(int argc, const char *argv[]) {
  float f0 = 3.14;
  float f1 = 2.7182;
  printf("pi %f stored as %8x\n", f0, *(unsigned int *)&f0);
  printf("e %f stored as %8x\n", f1, *(unsigned int *)&f1);
}
