#include "_lang_.h"
#include "lnk.h"
#include <assert.h>

/*
 * error: duplicate symbol
 * fn: declaration in lnk.h, definition in lnk.c
int fn(int x) {
  return x;
}
*/

/* function definition with internal linkage */
int
fn_l(int i) {
  return i*4;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

  int val = fn(1);
  assert(val == 0 + 0 + 3);

  /* declaration with external linkage in lnk.h, definition in lnk.c */
  state = 10;
  val = fn(1);
  assert(val == 10 + 0 + 3);

  /* size: read-only, defined in lnk.h with internal linkage */
  assert(size == 3);

  /* same identifier, declaration with internal linkage in lnk.c 
   * so compiler generates different instances.
   */
  int state_l = 1;
  val = fn(state_l);
  assert(val == 10 + 0 + 3);

  /* MAX in lnk.h */
  assert(MAX == 10);

  /* sum: inline function definition in lnk.h */
  val = sum(1, 2);
  assert(val == 1+2);

  /* state_c: extern definition in lnk.c */
  extern int state_c;
  state_c++;
  assert((0x12+1) == state_c);
  
  return 0;
}
