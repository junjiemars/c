#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <stk.h>

#define P
#define T double
#include <stk.h>


#define P
#include <str.h>
#define T str
#include <stk.h>



#define T image
#include <stk.h>

static void  test_stk_int(void);
static void  test_stk_double(void);
static void  test_stk_str(void);
static void  test_stk_image(void);


int
main(void)
{
  test_stk_int();
  test_stk_double();
  test_stk_str();
  test_stk_image();
}



void
test_stk_int(void)
{
  int  d1[]  =  {9, 1, 8, 3, 4};

  stk_int a = stk_int_init();

  for (size_t i = 0; i < _nof_(d1); i++)
    {
      stk_int_push(&a, d1[i]);
    }

  printf("stk<int>\n------------\n");


  stk_int_free(&a);
}

void
test_stk_double(void)
{
  double  d[]  =  {9.0, 1.0, 8.0, 3.0, 4.0};

  stk_double a = stk_double_init();

  for (size_t i = 0; i < _nof_(d); i++)
    {
      stk_double_push(&a, 9);
    }

  printf("stk<double>\n------------\n");


  stk_double_free(&a);
}

void
test_stk_str(void)
{
  char  *d[]  =  {"9a", "1a", "8a", "3a", "4a"};

  stk_str a = stk_str_init();

  for (size_t i = 0; i < _nof_(d); i++)
    {
      stk_str_push(&a, str_init(d[i]));
    }

  printf("stk<str>\n------------\n");

  stk_str_free(&a);
}

void
test_stk_image(void)
{
  stk_image a = stk_image_init();

  for(size_t i = 0; i < 5; i++)
    {
      stk_image_push(&a, image_read());
    }

  printf("stk<image>\n------------\n");

  stk_image b = stk_image_copy(&a);

  stk_image_free(&a);
  stk_image_free(&b);
}
