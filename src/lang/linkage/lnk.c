#include "lnk.h"

/* declaration with internal linkage */
static int fn_i(int);

/* declaration with internal linkage */
static int state_i = 0x1;

/* definition with external linkage */
int state;

/* declarations(twice here) with external linkage */
int state_c;
int state_c;

/* definition with external linkage */
int
fn(int x) {
    return state + state_i + fn_i(x);
}

int state_c = 0x1122;

/* definition with internal linkage */
int
fn_i(int i) {
    return i;
}

/* declaration with external linkage */
int fn_cube(int);


