#include "../_lang_.h"
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

void test_signed (void);

int
main (void)
{
  test_signed ();
}

void
test_signed (void)
{
  printf ("%s: %02zu bytes\nMIN:%032i\nMAX: %031i\n", "char", sizeof (char),
          CHAR_MIN, CHAR_MAX);

  printf ("%s: %02zu bytes\nMIN:%032i\nMAX: %031i\n", "short", sizeof (short),
          SHRT_MIN, SHRT_MAX);

  printf ("%s: %02zu bytes\nMIN:%032i\nMAX: %031i\n", "int", sizeof (int),
          INT_MIN, INT_MAX);

  printf ("%s: %02zu bytes\nMIN:%032li\nMAX: %031li\n", "long int",
          sizeof (long int), LONG_MIN, LONG_MAX);

  printf ("%s: %02zu bytes\nMIN:%032lli\nMAX: %031lli\n", "long long int",
          sizeof (long long int), LLONG_MIN, LLONG_MAX);
}
