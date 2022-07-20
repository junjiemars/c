#include "_lang_.h"
#include <assert.h>

void test_raw(int);
void test_ptr(int);
void test_ptr_ptr(int);


int
main(void)
{
  test_raw('a');
  test_ptr('a');
  test_ptr_ptr('a');

  return 0;
}

void
test_raw(int a)
{
  int d;
  d = a + 1;

  /* d + 1 is a value, not a lvalue */
  /* d + 1 = a; */

  assert(d);
}

void
test_ptr(int c)
{
  char *cp, *cp1;

  /* cp is a memory location, as a lvalue, so assignable */
  cp = (char*) &c;

  /* &c cannot be a lvalue, not assignable */
  /* &c = (char*) 0; */

  /* cp1 is a memory location */
  cp1 = cp;

  /* cp as rvalue */
  assert(*cp == (char) c);

  /* cp as lvalue */
  *cp = 'A';

  assert((*cp + 1) == 'B');

  /* a value not a lvalue */
  /* *cp + 1 = 'C'; */

  assert(cp1);
}

void
test_ptr_ptr(int c)
{
  char *cp;

  cp = (char*) &c;

  /* cpp = &cp; */

  assert(cp);
}
