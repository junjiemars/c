#include "ndef.h"
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


static void test_restrict(const char *restrict);
static void test_isut(void);
static void test_nof(void);
static void test_swp(void);


int
main(int argc, char **argv)
{
  _unused_(argc);

  test_restrict((const char *restrict) argv[0]);

  test_isut();
  test_nof();
  test_swp();

  return 0;
}


void
test_restrict(const char *restrict ss)
{
  _unused_(ss);
  printf("%s\n", __FUNCTION__);
}


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
  assert(_nof_(a) == sizeof(a)/sizeof(*a));
  printf("_nof_(a) = %zu\n", _nof_(a));
}


void
test_swp(void)
{
	int i1 = 0x1122, i2 = 0x3344;
	_swp_(&i1, &i2, sizeof(int));
	assert(0x1122 == i2 && 0x3344 == i1);

	int *p1 = &i1, *p2 = &i2;
	_swp_(&p1, &p2, sizeof(int*));
	assert(0x1122 == *p1 && 0x3344 == *p2);

	char *s1 = "abcdef", *s2 = "12345";
	_swp_(&s1, &s2, sizeof(char*));
	assert(strcmp("abcdef", s2) == 0 && strcmp("12345", s1) == 0);

	char sa1[] = "abcdef", sa2[] = "12345";
	char *ss1 = sa1, *ss2 = sa2;
	_swp_(&ss1, &ss2, sizeof(char*));
	assert(strcmp("abcdef", ss2) == 0 && strcmp("12345", ss1) == 0);
}
