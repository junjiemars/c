#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <ust.h>

#define P
#define T double
#include <ust.h>


#define P
#include <str.h>
#define T str
#include <ust.h>


#define T image
#include <ust.h>


static void  test_ust_int(void);
static void  test_ust_double(void);
static void  test_ust_str(void);
static void  test_ust_image(void);


int
main(void)
{
  test_ust_int();
  test_ust_double();
  test_ust_str();
  test_ust_image();
}


void
test_ust_int(void)
{
  int  d1[]  =  {9, 1, 8, 3, 4};

  ust_int a = ust_int_init(hash_int, equal_int);

  for (size_t i = 0; i < _nof_(d1); i++)
    {
      ust_int_insert(&a, d1[i]);
    }

  printf("ust<int>\n------------\n");

  foreach(ust_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  ust_int_free(&a);
}

void
test_ust_double(void)
{
  double  d[]  =  {9.0, 1.0, 8.0, 3.0, 4.0};

  ust_double a = ust_double_init(hash_double, equal_double);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      ust_double_insert(&a, 9);
    }

  printf("ust<double>\n------------\n");

  foreach(ust_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  ust_double_free(&a);
}

void
test_ust_str(void)
{
  char  *d[]  =  {"9a", "1a", "8a", "3a", "4a"};

  ust_str a = ust_str_init(hash_str, equal_str);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      ust_str_insert(&a, str_init(d[i]));
    }

  printf("ust<str>\n------------\n");

  foreach(ust_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  ust_str_free(&a);
}

void
test_ust_image(void)
{
  ust_image a = ust_image_init(hash_image, equal_image);

  for(size_t i = 0; i < 5; i++)
    {
      ust_image_insert(&a, image_read());
    }

  printf("ust<image>\n------------\n");

  foreach(ust_image, &a, it)
    {
      printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size);
    }

  ust_image b = ust_image_copy(&a);

  ust_image_free(&a);
  ust_image_free(&b);
}
