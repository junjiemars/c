#include "f1.h"


float
add(float x, float y)
{
  float z = x + y;
  return z;
}

float
add_and_mul(float x, float y)
{
  float z = add(x, y);
  z *= MUL;
  return z;
}
