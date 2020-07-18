#include "_lang_.h"
#include "bits.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#if defined(BIT8_SEP)
#  undef  BIT8_SEP
#  define BIT8_SEP " "
#endif

#if defined(BIT16_SEP)
#  undef  BIT16_SEP
#  define BIT16_SEP " "
#endif

unsigned int to_ui(float);
unsigned long to_ul(double);

void test_cmp_float(void);
void test_cmp_double(void);
void test_asm_double(void);
void test_episilon_double(void);

unsigned int
to_ui(float x) {
  unsigned int u;
  memcpy((char*)&u, (char*)&x, sizeof(x));
  return u;
}

unsigned long
to_ul(double x) {
  unsigned long u;
  memcpy((char*)&u, (char*)&x, sizeof(x));
  return u;
}

void
test_cmp_float(void) {
  float d1 = 0.1, d2 = 0.2, d3 = 0.3;
  unsigned int u1 = to_ui(d1);
  unsigned int u2 = to_ui(d2);
  unsigned int u12 = to_ui(d1+d2);
  unsigned int u3 = to_ui(d3);

  printf("compare float\n--------------------\n");
  printf("%16f = 0x%X\n", d1, u1);
  printf("%16f = 0x%X\n", d2, u2);
  printf("%16f = 0x%X\n", d1+d2, u12);
  printf("%16f = 0x%X\n", d3, u3);

  printf(BPRI32(u1));
  printf(BPRI32(u2));
  printf(BPRI32(u12));
  printf(BPRI32(u3));

  assert(u3 == u12);
  assert(d3 == d1 + d2);
  
  int less, greater, lessgreater, unordered, lessequal, greaterequal;
  less = isless(d3, d1+d2);
  greater = islessgreater(d3, d1+d2);
  lessgreater = islessgreater(d3, d1+d2);
  lessequal = islessequal(d3, d1+d2);
  greaterequal = isgreaterequal(d3, d1+d2);
  unordered = isunordered(d3, d1+d2);

  assert(!unordered);
  assert(!less);
  assert(!greater);
  assert(!lessgreater);
  assert((less || greater) == lessgreater);
  assert(lessequal && greaterequal);

  int less1, greater1, lessgreater1;
  float lg1 = 0.1, lg2 = 0.2, lg3 = 0.3001;
  less1 = isless(lg3, lg1+lg2);
  greater1 = isgreater(lg3, lg1+lg2);
  lessgreater1 = islessgreater(lg3, lg1+lg2);

  assert(less1 || greater1);
  assert(lessgreater1);
  assert((less1 || greater1) == lessgreater1);
}

void
test_cmp_double(void) {
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  unsigned long u1 = to_ul(d1);  
  unsigned long u2 = to_ul(d2);
  unsigned long u12 = to_ul(d1+d2);
  unsigned long u3 = to_ul(d3); 

  printf("compare double\n--------------------\n");
  printf("%16lf = 0x%lX\n", d1, to_ul(d1));
  printf("%16lf = 0x%lX\n", d2, to_ul(d2));
  printf("%16lf = 0x%lX\n", d1+d2, to_ul(d1+d2));
  printf("%16lf = 0x%lX\n", d3, to_ul(d3));

  printf(BPRI64(u1));
  printf(BPRI64(u2));
  printf(BPRI64(u12));
  printf(BPRI64(u3));

  assert(u3 != u12);
  assert(d3 != d1 + d2);
  
  int less, greater, lessgreater, unordered, lessequal, greaterequal;
  less = isless(d3, d1+d2);
  greater = islessgreater(d3, d1+d2);
  lessgreater = islessgreater(d3, d1+d2);
  lessequal = islessequal(d3, d1+d2);
  greaterequal = isgreaterequal(d3, d1+d2);
  unordered = isunordered(d3, d1+d2);

  assert(!unordered);
  assert(less);
  assert(greater);
  assert(lessgreater);
  assert(lessequal || greaterequal);
  assert(less && greater);

  int less1, greater1, lessgreater1;
  double lg1 = 0.1, lg2 = 0.2, lg3 = 0.3001;
  less1 = isless(lg3, lg1+lg2);
  greater1 = isgreater(lg3, lg1+lg2);
  lessgreater1 = islessgreater(lg3, lg1+lg2);

  assert(less1 || greater1);
  assert(lessgreater1);
  assert((less1 || greater1) == lessgreater1);
}

void
test_asm_double(void) {
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  int x = ((d1+d2) - d3);
  _unused_(x);
}

void
test_episilon_double(void) {
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  double episilon = 0.00001;
  int x = fabs((d1+d2) - d3) < episilon;
  _unused_(x);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  test_cmp_float();
  test_cmp_double();
  test_asm_double();
  test_episilon_double();
  
  return 0;
}
