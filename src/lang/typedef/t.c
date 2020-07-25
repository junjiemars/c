#include "_lang_.h"
#include <stdio.h>


/* syntax: typedef type declaration */
typedef int length_t;

struct point_s /* tag: not type */ {
	int x;
	int y;
};
typedef struct point_s point_t;

typedef struct point1_s {
	int x;
	int y;
} point1_t /* type */;

/* x_t alias of int */
/* p_t alias of pointer to int */
/* f_t as function accept int and return pointer to int */
typedef int x_t, *p_t, *(*fn_t)(int);

p_t fn(int n) {
  x_t x = n + 10;
  p_t p = &x;
  return p;
}

void
test_fn(void) {
  fn_t f1 = fn;
  p_t p = f1(3);
  printf("test_fn(3)        = %4i\n", *p);
}

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("sizeof(length_t)  = %4zu\n", sizeof(length_t));
  printf("sizeof(point_t)   = %4zu\n", sizeof(point_t));
  printf("sizeof(point1_t)  = %4zu\n", sizeof(point1_t));
  printf("sizeof(x_t)       = %4zu\n", sizeof(x_t));
  printf("sizeof(p_t)       = %4zu\n", sizeof(p_t));
  printf("sizeof(f_t)       = %4zu\n", sizeof(fn_t));
  
  test_fn();
  
  return 0;
}
