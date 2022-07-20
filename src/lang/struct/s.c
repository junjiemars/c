#include "_lang_.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if (MSVC)
#  pragma warning(disable: 4200)
#endif

struct flex1_s {
  int n;
  long n2[];  /* flexibile member */
};

#if defined(GCC) || defined(CLANG)
struct __attribute__((packed)) flex2_s {
  int n;
  long n2[]; /* flexibile member */
};
#elif defined(MSVC)
#  pragma pack(push, 1)
struct flex2_s {
  int n;
  long n2[]; /* flexibile member */
};
#  pragma pack(pop)
#endif

struct noname1_s {
  uint16_t n;
  struct { /* anonymous struct */
    uint16_t a;
    uint16_t b;
  } noname;
};


#if defined(GCC) || defined(CLANG)
struct __attribute__((packed)) noname2_s {
  uint16_t n;
  struct { /* anonymous struct */
    uint16_t a;
    uint16_t b;
  } noname;
};
#elif defined(MSVC)
#  pragma pack(push, 1)
struct noname2_s {
  uint16_t n;
  struct { /* anonymous struct */
    uint16_t a;
    uint16_t b;
  } noname;
};
#  pragma pack(pop)
#endif

struct cyclic1_y;

struct cyclic1_x {
  int nx;
  struct cyclic1_y *y; /* if not pointer type that is incomplete type */
};

struct cyclic1_y {
  int ny;
  struct cyclic1_x x;
};


#if defined(GCC) || defined(CLANG)
struct cyclic2_y;

struct __attribute__((packed)) cyclic2_x {
  int nx;
  struct cyclic2_y *y; /* if not pointer type that is incomplete type */
};

struct __attribute__((packed)) cyclic2_y {
  int ny;
  struct cyclic2_x x;
};
#elif defined(MSVC)
#pragma pack(push, 1)
struct cyclic2_y;

struct cyclic2_x {
  int nx;
  struct cyclic2_y *y; /* if not pointer type that is incomplete type */
};

struct cyclic2_y {
  int ny;
  struct cyclic2_x x;
};
#pragma pack(pop)
#endif

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

struct padding_s {
  int a;
  char b;
};

#if defined(GCC) || defined(CLANG)
struct __attribute__((packed)) packed_s {
  int a;
  char b;
};
#elif defined(MSVC)
#pragma pack(push, 1)
struct packed_s {
  int a;
  char b;
};
#pragma pack(pop)
#endif

void test_flex1_s(void);
void test_flex2_s(void);
void test_noname1_s(void);
void test_noname2_s(void);
void test_cyclic1_s(void);
void test_cyclic2_s(void);
void test_nest_s(void);
void test_padding_s(void);
void test_packed_s(void);

void
test_flex1_s(void) {
  struct flex1_s fs1 = { 0 };
  printf("sizeof(fs1) = %zu\n", sizeof(fs1));
  /* fs1.n2[0] = 0x1; */
  /* fs1.n2 flexibile member, no space had been allocated */

  /* initialization of flexible array member is not allowed */
  /* struct flex1_s fs2 = { .n = 1, .n2= { 0x11, 0x22 } }; */
  struct flex1_s fs3 = { .n = 1 };
  printf("sizeof(fs3) = %zu\n", sizeof(fs3));

  /* n2[8] */
  struct flex1_s *fs64 = malloc(sizeof(struct flex1_s) + sizeof(long)*8);
  /* n2[1] */
  struct flex1_s *fsd2 = malloc(sizeof(struct flex1_s) + sizeof(long)+2);

  for (int i = 0; i < 8; i++) {
    fs64->n2[i] = i;
  }
  for (int i = 0; i < 8; i++) {
    printf("fs64->n2[%d] = %8li\n", i, fs64->n2[i]);
  }

  /* head buffer overflow */
  for (int i = 0; i < 1; i++) {
    fsd2->n2[i] = i;
  }
  for (int i = 0; i < 1; i++) {
    printf("fsd2->n2[%d] = %8li\n", i, fsd2->n2[i]);
  }

  free(fs64);
  free(fsd2);
}

void
test_flex2_s(void) {
  struct flex2_s fs1 = {0};
  printf("sizeof(fs1) = %4zu\n", sizeof(fs1));
}

void
test_noname1_s(void) {
  struct noname1_s nn1 = {0};
  printf("sizeof(nn1) = %4zu\n", sizeof(nn1));

  nn1.n = 0x1;
  nn1.noname.a = 0x2;
  nn1.noname.b = 0x3;
}

void
test_noname2_s(void) {
  struct noname2_s nn1 = {0};
  printf("sizeof(nn1) = %4zu\n", sizeof(nn1));

  nn1.n = 0x1;
  nn1.noname.a = 0x2;
  nn1.noname.b = 0x3;
}

void
test_cyclic1_s(void) {
  struct cyclic1_x x = { 0 };
  struct cyclic1_y y = { 0 };
  printf("sizeof(x) = %4zu\n", sizeof(x));
  printf("sizeof(y) = %4zu\n", sizeof(y));
}

void
test_cyclic2_s(void) {
  struct cyclic2_x x = { 0 };
  printf("sizeof(x) = %4zu\n", sizeof(x));

  struct cyclic2_y y = { 0 };
  y.ny = 0x11223344;
  y.x.nx = 0xaabbccdd;
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

void
test_padding_s(void) {
  struct padding_s *p1 = malloc(sizeof(struct padding_s));
  printf("sizeof(padding_s) = %zu\n", sizeof(struct padding_s));

  free(p1);
}

void
test_packed_s(void) {
  struct packed_s *p1 = malloc(sizeof(struct packed_s));
  printf("sizeof(packed_s) = %zu\n", sizeof(struct packed_s));

  free(p1);
}

int
main(void) {

  test_flex1_s();
  test_flex2_s();
  test_noname1_s();
  test_noname2_s();
  test_cyclic1_s();
  test_cyclic2_s();
  test_nest_s();
  test_padding_s();
  test_packed_s();

  return 0;
}
