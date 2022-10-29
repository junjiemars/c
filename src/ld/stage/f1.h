#pragma once

#define FIRST_OPTION

#ifdef FIRST_OPTION
#  define MUL  (3.0)
#else
#  define MUL  (2.0)
#endif

float add_and_mul(float x, float y);

int n_status;
