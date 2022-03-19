#include "ndef.h"
#include <inttypes.h>
#include <stdio.h>


static void test_restrict(const char *restrict);
/* static void test_static_assert(void); */

static void test_isut(void);
static void test_nof(void);


int
main(int argc, char **argv)
{
  _unused_(argc);

  /* test_static_assert(); */
  test_restrict((const char *restrict) argv[0]);

  test_isut();
  test_nof();

  return 0;
}


void
test_restrict(const char *restrict ss)
{
  _unused_(ss);
  printf("%s\n------------\n", __FUNCTION__);
}


/* void */
/* test_static_assert(void) */
/* { */
/*   static_assert(sizeof(char) == 1, "sizeof(char) is not 1 byte"); */
/*   printf("%s\n------------\n", __FUNCTION__); */
/* } */


void
test_isut(void)
{
  printf("_isut_(char) = %d\n_isut_(unsigned char) = %d\n",
         _isut_(char), _isut_(unsigned char));
}


void
test_nof(void)
{
  int a[] = { 1, 2, 3, };
  printf("_nof_(a) = %zu\n", _nof_(a));
}
