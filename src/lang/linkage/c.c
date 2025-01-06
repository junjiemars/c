#include "../_lang_.h"
#include "lnk.h"

static int fn_i (int);
extern int fn_cube (int);

static int state_i = 0x1122;

int
main (void)
{

  int val = fn (1);
  assert (val == state + 0x1 /* state_i:lnk.c */ + 1);

  state = 10; /* state:lnk.c */
  val = fn (1);
  assert (val != (state + state_i + 1));
  assert (val == 10 + 0x1 /* == state_i:lnk.c */ + 1);

  /* size: read-only, defined in lnk.h with internal linkage */
  assert (size == 3);

  /* same identifier, declaration with internal linkage in lnk.c
   * so compiler generates different instances.
   */
  val = fn_i (state_i);
  assert (val != state_i);
  assert (val == state_i * state_i);

  /* MAX:lnk.h */
  assert (MAX == 10);

  /* state_c: extern declaration in lnk.c */
  extern int state_c;
  state_c += 0x1122;
  assert (0x2244 == state_c);

  val = fn_cube (3);
  assert (3 * 3 * 3 == val);

  return 0;
}

int
fn_i (int i)
{
  return i * i;
}

extern int
fn_cube (int a)
{
  return a * a * a;
}
