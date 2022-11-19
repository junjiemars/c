#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <deq.h>

#define P
#define T double
#include <deq.h>


#define P
#include <str.h>
#define T str
#include <deq.h>


#define T image
#include <deq.h>


static void  test_deq_int(void);
static void  test_deq_double(void);
static void  test_deq_str(void);
static void  test_deq_image(void);


int
main(void)
{
  test_deq_int();
  test_deq_double();
  test_deq_str();
  test_deq_image();
}

void
test_deq_int(void)
{
  deq_int a = deq_int_init();

  deq_int_push_back(&a, 9);
  deq_int_push_back(&a, 1);
  deq_int_push_back(&a, 8);
  deq_int_push_back(&a, 3);
  deq_int_push_back(&a, 4);

  deq_int_sort(&a, compare_int);

  printf("deq<int>\n------------\n");
  foreach(deq_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  deq_int_free(&a);
}

void
test_deq_double(void)
{
  deq_double a = deq_double_init();

  deq_double_push_back(&a, 9);
  deq_double_push_back(&a, 1);
  deq_double_push_back(&a, 8);
  deq_double_push_back(&a, 3);
  deq_double_push_back(&a, 4);

  deq_double_sort(&a, compare_double);

  printf("deq<double>\n------------\n");
  foreach(deq_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  deq_double_free(&a);
}

void
test_deq_str(void)
{
  deq_str a = deq_str_init();

  deq_str_push_back(&a, str_init("9aaa"));
  deq_str_push_back(&a, str_init("1aaa"));
  deq_str_push_back(&a, str_init("8aaa"));
  deq_str_push_back(&a, str_init("3aaa"));
  deq_str_push_back(&a, str_init("4aaa"));

  deq_str_sort(&a, compare_str);

  printf("deq<str>\n------------\n");
  foreach(deq_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  deq_str_free(&a);
}

void
test_deq_image(void)
{
  deq_image a = deq_image_init();
  for(size_t i = 0; i < 5; i++)
    {
      deq_image_push_back(&a, image_read());
    }
  deq_image_sort(&a, compare_image);

  printf("deq<image>\n------------\n");
  foreach(deq_image, &a, it)
    {
      printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size);
    }

  deq_image b = deq_image_copy(&a);
  deq_image_free(&a);
  deq_image_free(&b);
}
