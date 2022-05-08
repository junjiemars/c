#include <_algo_.h>
#include "permute.h"

void
permute(void *base, size_t n, size_t width, const size_t *permutation,
        int (*cmp)(const void *, const void *))
{
  size_t   i;
  char    *src, *dst;

  for (i = 0; i < n; i++)
    {
      if (permutation[i] >= n)
        {
          break;
        }

      src = (char *) base + width * i;
      dst = (char *) base + width * permutation[i];

      if (src == dst || 0 == cmp(src, dst))
        {
          continue;
        }

      _swp_(src, dst, width);
    }
}
