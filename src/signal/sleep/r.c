#include "_signal_.h"


void race(long);

void
race(long n)
{
  _unused_(volatile double  d)  =  0;

  for (long i = 0; i < n; i++)
    {
      d += rand() * n;
    }
}
