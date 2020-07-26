#include "lnk.h"

/* definition with internal linkage */
static int
fn_l(int i) {
  return i*3;
}

/* definition with internal linkage */
static int state_l;

/* definition with external linkage */
int state;

/* definition with external linkage */
int
fn(int x) {
  return state + state_l + fn_l(x);
}
