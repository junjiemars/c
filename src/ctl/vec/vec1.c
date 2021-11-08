#include "_ctl_.h"
#include <stdio.h>

#define P
#define T int
#include <vec.h>

#define P
#define T double
#include <vec.h>


#include <str.h>
#define T str
#include <vec.h>


static int compare_int(int *a, int *b);
static int compare_double(double *a, double *b);
static int compare_str(str *a, str *b);

static void test_vec_int(void);
static void test_vec_double(void);
static void test_vec_str(void);


int
compare_int(int* a, int* b)
{
  return (*a) > (*b);
}

int
compare_double(double *a, double *b)
{
  return (*a) > (*b);
}

int
compare_str(str *a, str *b)
{
  return strcmp(str_c_str(a), str_c_str(b));
}


void
test_vec_int(void)
{
  vec_int a = vec_int_init();

  vec_int_push_back(&a, 9);
  vec_int_push_back(&a, 1);
  vec_int_push_back(&a, 8);
  vec_int_push_back(&a, 3);
  vec_int_push_back(&a, 4);

  vec_int_sort(&a, compare_int);

  foreach(vec_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  vec_int_free(&a);
}

void
test_vec_double(void)
{
  vec_double a = vec_double_init();

  vec_double_push_back(&a, 9);
  vec_double_push_back(&a, 1);
  vec_double_push_back(&a, 8);
  vec_double_push_back(&a, 3);
  vec_double_push_back(&a, 4);

  vec_double_sort(&a, compare_double);

  foreach(vec_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  vec_double_free(&a);
}

void
test_vec_str(void)
{
  vec_str a = vec_str_init();

  vec_str_push_back(&a, str_init("9aaa"));
  vec_str_push_back(&a, str_init("1aaa"));
  vec_str_push_back(&a, str_init("8aaa"));
  vec_str_push_back(&a, str_init("3aaa"));
  vec_str_push_back(&a, str_init("4aaa"));

  vec_str_sort(&a, compare_str);

  foreach(vec_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  vec_str_free(&a);
}

int main(void)
{
  test_vec_int();
  test_vec_double();
  test_vec_str();
}
