#include "_lang_.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct flex_s {
  uint16_t n;
  uint32_t n2[];  /* flexibile member */
};

struct noname_s {
  uint16_t n;
  struct { /* anonymous struct */
    uint16_t a;
    uint16_t b;
  } noname;
};

struct cyclic_y;

struct cyclic_x {
  uint16_t nx;
  struct cyclic_y *y; /* if not pointer type that is incomplete type */
};

struct cyclic_y {
  uint16_t ny;
  struct cyclic_x x;
};

#define _OVERLAP_                               \
  char *base;                                   \
  size_t len;

struct nest1_s {
  _OVERLAP_
  uint16_t x;
};

struct nest2_s {
  _OVERLAP_
  char y[16];
};

void test_flex_s(void);
void test_noname_s(void);
void test_cyclic_s(void);
void test_nest_s(void);

void
test_flex_s(void) {
  struct flex_s fs1 = { 0 };
  printf("sizeof(fs1) = %zu\n", sizeof(fs1));
  /* fs1.n[0] = 0x1; */
  /* fs1.n2 flexibile member, no space had been allocated */

  /* initialization of flexible array member is not allowed */
  /* struct flex_s fs2 = { .n = 1, .n2= { 0x11, 0x22 } }; */
  struct flex_s fs3 = { .n = 1 };
  printf("sizeof(fs3) = %zu\n", sizeof(fs3));

  /* n2[8] */
  struct flex_s *fs64 = malloc(sizeof(struct flex_s) + sizeof(uint32_t)*8);
  /* n2[1] */
  struct flex_s *fsd2 = malloc(sizeof(struct flex_s) + sizeof(uint32_t)+2);

  for (int i = 0; i < 8; i++) {
    fs64->n2[i] = i;
  }
  for (int i = 0; i < 8; i++) {
    printf("fs64->n2[%d] = %8i\n", i, fs64->n2[i]);
  }

  /* head buffer overflow */
  for (int i = 0; i < 1; i++) {
    fsd2->n2[i] = i;
  }
  for (int i = 0; i < 1; i++) {
    printf("fsd2->n2[%d] = %8i\n", i, fsd2->n2[i]);
  }
  
  free(fs64);
  free(fsd2);
}

void
test_noname_s(void) {
  struct noname_s nn1 = {0};
  printf("sizeof(nn1) = %4zu\n", sizeof(nn1));

  nn1.n = 0x1;
  nn1.noname.a = 0x2;
  nn1.noname.b = 0x3;
}

void
test_cyclic_s(void) {
  struct cyclic_x x = { 0 };
  printf("sizeof(x) = %4zu\n", sizeof(x));

  struct cyclic_y y = { 0 };
  printf("sizeof(y) = %4zu\n", sizeof(y));
}

void
test_nest_s(void) {
  struct nest1_s *n1 = malloc(sizeof(struct nest1_s));
  printf("sizeof(nest1_s) = %4zu\n", sizeof(struct nest1_s));

  n1->base = "abc";
  n1->len = strlen(n1->base);

  struct nest1_s *n11 = (struct nest1_s*)&n1->base;
  printf("n11->base = %s, %zu\n", n11->base, n11->len);

  struct nest2_s *n2 = (struct nest2_s*)n11;
  printf("n2->base = %s, %zu\n", n2->base, n2->len);

  struct nest2_s *n21 = (struct nest2_s*)&n1->base;
  printf("n21->base = %s, %zu\n", n21->base, n21->len);
  
  free(n1);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
  test_flex_s();
  test_noname_s();
  test_cyclic_s();
  test_nest_s();

  return 0;
}
