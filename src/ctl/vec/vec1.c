#include <_ctl_.h>
#include <stdio.h>

#define P
#define T int
#include <vec.h>

int compare(int* a, int* b)
{
  return *b < *a;
}

int main(void)
{
  vec_int a = vec_int_init();

  vec_int_push_back(&a, 9);
  vec_int_push_back(&a, 1);
  vec_int_push_back(&a, 8);
  vec_int_push_back(&a, 3);
  vec_int_push_back(&a, 4);

  vec_int_sort(&a, compare);

  foreach(vec_int, &a, it)
    printf("%d\n", *it.ref);

  vec_int_free(&a);
}
