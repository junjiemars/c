/*
 * cc -E x.c
 * will in preprocessing stage: handles tokenization of the input source file,
 * macro expansion, #include expansion and handling of other preprocessor directives.
 */
#include "x.h"

int minus(int a, int b) {
  int n = a-b;
  return n;
  }

int main(int argc, const char *argv[]) {
  int n = 0;
  n = minus(add(3, 4), 5);
  }
