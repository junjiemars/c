#include "lnk.h"

/* definition with internal linkage */
static int
fn_l(int i) {
  return i * size;
}

/* definition with internal linkage */
static int state_l;

/* definition with external linkage */
int state;

/* declaration with external linkage */
extern int state_c = 0x12;

/* definition with external linkage */
int
fn(int x) {
  return state + state_l + fn_l(x);
}
