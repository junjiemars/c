#include "_ctl_.h"

#define P
#define T int
#include <que.h>

#define P
#define T double
#include <que.h>

#define P
#include <str.h>
#define T str
#include <que.h>

#define T image
#include <que.h>

static void test_que_int (void);
static void test_que_double (void);
static void test_que_str (void);
static void test_que_image (void);

int
main (void)
{
  test_que_int ();
  test_que_double ();
  test_que_str ();
  test_que_image ();
}

void
test_que_int (void)
{
  int d[] = { 9, 1, 8, 3, 4 };

  que_int a = que_int_init ();

  assert (que_int_empty (&a));

  for (size_t i = 0; i < _nof_ (d); i++)
    {
      que_int_push (&a, d[i]);
    }

  assert (a.size == _nof_ (d));
  assert (*que_int_front (&a) == d[0]);
  assert (*que_int_back (&a) == d[_nof_ (d) - 1]);

  printf ("que<int>\n------------\n");
  while (!que_int_empty (&a))
    {
      printf ("%d\n", *que_int_front (&a));
      que_int_pop (&a);
    }

  assert (que_int_empty (&a));

  que_int_free (&a);
}

void
test_que_double (void)
{
  double d[] = { 9.0, 1.0, 8.0, 3.0, 4.0 };

  que_double a = que_double_init ();

  for (size_t i = 0; i < _nof_ (d); i++)
    {
      que_double_push (&a, d[i]);
    }

  printf ("que<double>\n------------\n");
  while (!que_double_empty (&a))
    {
      printf ("%lf\n", *que_double_front (&a));
      que_double_pop (&a);
    }

  que_double_free (&a);
}

void
test_que_str (void)
{
  char *d[] = { "9a", "1a", "8a", "3a", "4a" };

  que_str a = que_str_init ();

  for (size_t i = 0; i < _nof_ (d); i++)
    {
      que_str_push (&a, str_init (d[i]));
    }

  printf ("que<str>\n------------\n");

  while (!que_str_empty (&a))
    {
      printf ("\"%s\"\n", str_c_str (que_str_front (&a)));
      que_str_pop (&a);
    }

  que_str_free (&a);
}

void
test_que_image (void)
{
  que_image a = que_image_init ();

  for (size_t i = 0; i < 5; i++)
    {
      que_image_push (&a, image_read ());
    }

  printf ("que<image>\n------------\n");

  while (!que_image_empty (&a))
    {
      image *it = que_image_front (&a);

      printf ("{ %d, %zu }\n", *it->data, it->size);
      que_image_pop (&a);
    }

  que_image b = que_image_copy (&a);

  que_image_free (&a);
  que_image_free (&b);
}
