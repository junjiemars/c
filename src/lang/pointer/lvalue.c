#include "_lang_.h"
#include <assert.h>

void test_raw(int);
void test_ptr(int);
void test_ptr_ptr(int);

void
test_raw(int a) {
  int d;
  d = a + 1;
  
  /* d + 1 is a value, not a lvalue */
  /* d + 1 = a; */

  ASSERT(d);
}

void
test_ptr(int c) {
  char *cp, *cp1;
  
  /* cp is a memory location, as a lvalue, so assignable */
  cp = (char*) &c;

  /* &c cannot be a lvalue, not assignable */
  /* &c = (char*) 0; */

  /* cp1 is a memory location */
  cp1 = cp;

  /* cp as rvalue */
  ASSERT(*cp == (char) c);

  /* cp as lvalue */
  *cp = 'A';

  ASSERT((*cp + 1) == 'B');

  /* a value not a lvalue */
  /* *cp + 1 = 'C'; */
  
  ASSERT(cp1);
}

void
test_ptr_ptr(int c) {
  char *cp;

  cp = (char*) &c;

  /* cpp = &cp; */

  ASSERT(cp);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  test_raw('a');
  test_ptr('a');
  test_ptr_ptr('a');

  return 0;
}
