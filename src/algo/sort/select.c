#include <_algo_.h>
#include "sort.h"

void
sort(void *base, size_t n, size_t width,
     int (*cmp)(const void *lhs, const void *rhs))
{
  size_t  i, j;
  size_t  min;

	for (i = 0; i < n; i++)
    {
      min = i;
      for (j = i+1; j < n; j++)
        {
          if (cmp((char*) base + min*width, (char*) base + j*width) > 0)
            {
              min = j;
            }
        }
      if (i != min)
        {
          _swp_((char*) base + min*width, (char*) base + i*width, width);
        }
    }
}

/* eof */
