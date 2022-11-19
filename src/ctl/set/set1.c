#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <set.h>

#define P
#define T double
#include <set.h>


#define P
#include <str.h>
#define T str
#include <set.h>



#define T image
#include <set.h>


static void  test_set_int(void);
static void  test_set_double(void);
static void  test_set_str(void);
static void  test_set_image(void);


int
main(void)
{
  test_set_int();
  test_set_double();
  test_set_str();
  test_set_image();
}


void
test_set_int(void)
{
  int  d1[]  =  {9, 1, 8, 3, 4};

  set_int a = set_int_init(compare_int);

  for (size_t i = 0; i < _nof_(d1); i++)
    {
      set_int_insert(&a, d1[i]);
    }

  printf("set<int>\n------------\n");

  foreach(set_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  set_int_free(&a);
}

void
test_set_double(void)
{
  double  d[]  =  {9.0, 1.0, 8.0, 3.0, 4.0};

  set_double a = set_double_init(compare_double);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      set_double_insert(&a, 9);
    }

  printf("set<double>\n------------\n");

  foreach(set_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  set_double_free(&a);
}

void
test_set_str(void)
{
  char  *d[]  =  {"9a", "1a", "8a", "3a", "4a"};

  set_str a = set_str_init(compare_str);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      set_str_insert(&a, str_init(d[i]));
    }

  printf("set<str>\n------------\n");

  foreach(set_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  set_str_free(&a);
}

void
test_set_image(void)
{
  set_image a = set_image_init(compare_image);

  for(size_t i = 0; i < 5; i++)
    {
      set_image_insert(&a, image_read());
    }

  printf("set<image>\n------------\n");

  foreach(set_image, &a, it)
    {
      printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size);
    }

  set_image b = set_image_copy(&a);

  set_image_free(&a);
  set_image_free(&b);
}
