#include "_ctl_.h"

#define P
#define T int
#include <pqu.h>

#define P
#define T double
#include <pqu.h>

#define P
#include <str.h>
#define T str
#include <pqu.h>

#define T image
#include <pqu.h>

static void test_pqu_int (void);
static void test_pqu_double (void);
static void test_pqu_str (void);
static void test_pqu_image (void);

int
main (void)
{
  test_pqu_int ();
  test_pqu_double ();
  test_pqu_str ();
  test_pqu_image ();
}

void
test_pqu_int (void)
{
  pqu_int a = pqu_int_init (compare_int);

  pqu_int_push (&a, 9);
  pqu_int_push (&a, 1);
  pqu_int_push (&a, 8);
  pqu_int_push (&a, 3);
  pqu_int_push (&a, 4);

  /* pqu_int_sort(&a, compare_int); */

  printf ("pqu<int>\n------------\n");
  /* foreach(pqu_int, &a, it) */
  /*   { */
  /*     printf("%d\n", *it.ref); */
  /*   } */

  pqu_int_free (&a);
}

void
test_pqu_double (void)
{
  pqu_double a = pqu_double_init (compare_double);

  pqu_double_push (&a, 9);
  pqu_double_push (&a, 1);
  pqu_double_push (&a, 8);
  pqu_double_push (&a, 3);
  pqu_double_push (&a, 4);

  /* pqu_double_sort(&a, compare_double); */

  printf ("pqu<double>\n------------\n");
  /* foreach(pqu_double, &a, it) */
  /*   { */
  /*     printf("%lf\n", *it.ref); */
  /*   } */

  pqu_double_free (&a);
}

void
test_pqu_str (void)
{
  pqu_str a = pqu_str_init (compare_str);

  pqu_str_push (&a, str_init ("9aaa"));
  pqu_str_push (&a, str_init ("1aaa"));
  pqu_str_push (&a, str_init ("8aaa"));
  pqu_str_push (&a, str_init ("3aaa"));
  pqu_str_push (&a, str_init ("4aaa"));

  /* pqu_str_sort(&a, compare_str); */

  printf ("pqu<str>\n------------\n");
  /* foreach(pqu_str, &a, it) */
  /*   { */
  /*     printf("\"%s\"\n", str_c_str(it.ref)); */
  /*   } */

  pqu_str_free (&a);
}

void
test_pqu_image (void)
{
  pqu_image a = pqu_image_init (compare_image);
  for (size_t i = 0; i < 5; i++)
    {
      pqu_image_push (&a, image_read ());
    }
  /* pqu_image_sort(&a, compare_image); */

  printf ("pqu<image>\n------------\n");
  /* foreach(pqu_image, &a, it) */
  /*   { */
  /*     printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size); */
  /*   } */

  pqu_image b = pqu_image_copy (&a);
  pqu_image_free (&a);
  pqu_image_free (&b);
}
