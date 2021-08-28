#include <_algo_.h>
#include "sort.h"

void
sort(void *base, size_t n, size_t width,
     int (*cmp)(const void *, const void *))
{
  size_t  i, j;

	for (i = 0; i < n; i++)
    {
      for (j = 0; j < n-i-1; j++)
        {
          if (cmp((char*) base + j*width, (char*) base + (j+1)*width) > 0)
            {
              swap((char*) base + j*width, (char*) base + (j+1)*width, width);
            }
        }
    }
}


/* eof */
