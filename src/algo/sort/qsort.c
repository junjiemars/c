#include <_algo_.h>
#include "sort.h"


void
sort(void *base, size_t n, size_t width,
     int (*cmp)(const void *, const void *))
{
  char  *pivot, *lo, *hi;

  if (n < 2)
    {
      return;
    }

  pivot = (char *) base;
  lo = (char *) base - width;
  hi = (char *) base + n * width;

  while (lo < hi)
    {
      do
        {
          hi -= width;
        } while (cmp(hi, pivot) > 0);
      do
        {
          lo += width;
        } while (cmp(lo, pivot) < 0);
      if (lo < hi)
        {
          swap(lo, hi, width);
        }
    }

  sort(base, offset(base, hi + width, width), width, cmp);
  sort(hi + width, n - offset(base, hi + width, width), width, cmp);
}
