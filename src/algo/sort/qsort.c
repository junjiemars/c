#include <_algo_.h>
#include "sort.h"


void
sort(void *base, size_t n, size_t width,
     int (*cmp)(const void *, const void *))
{
  size_t  p, i;
  
  if (n < 2)
    {
      return;
    }

  p = n / 2;
  for (i = 0; i < n; i++)
    {
      
    }
  
  sort(base, p, width, cmp);
  sort((char *) base + (p+1)*width, n - p, width, cmp);
}
