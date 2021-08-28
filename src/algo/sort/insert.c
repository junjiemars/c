#include <_algo_.h>
#include "sort.h"


void
sort(void *base, size_t n, size_t width,
     int (*cmp)(const void *, const void *))
{
  size_t      j;
  long long   i;
	void       *saved  =  0;

  saved = malloc(width);

	for (j = 1; j < n; j++)
    {
      i = (long long) j-1;
      while (i >= 0 && cmp((char*) base + i*width, (char*) base + j*width) > 0)
        {
          i--;
        }
      if ((long long) j == ++i /* important */)
        {
          continue;
        }
      memmove(saved, (char*) base + j*width, width);
      memmove((char*) base + (i+1)*width, (char*) base + i*width, (j-i)*width);
      memmove((char*) base + i*width, saved, width);
    }

	free(saved);
}

/* eof */
