#include <nio.h>
#include <stdlib.h>


#if !(NM_HAVE_GETDELIM)

ssize_t
getdelim(char ** restrict lineptr, size_t * restrict n, int delimiter,
         FILE * restrict stream)
{
	int       c;
	char     *p, *p1;
	ssize_t   len;

  if (0 == lineptr)
    {
      return EOF;
    }
	if (0 == *lineptr)
    {
      *n = NM_LINE_MAX;
      *lineptr = malloc(*n);
      if (0 == *lineptr)
        {
          return EOF;
        }
    }
  p = *lineptr;
  len = 0;

	while (EOF != (c = fgetc(stream)))
    {
      if ((size_t) len == (*n - 1))
        {
          *n <<= 1;
          p1 = realloc(*lineptr, *n);
          if (0 == p1)
            {
              return EOF;
            }
          *lineptr = p1;
          p = p1 + len;
        }
      *p++ = (char) c;
      len++;

      if (c == delimiter)
        {
          break;
        }
    }

  *p = 0;
	return len;
}

#endif  /* NM_HAVE_GETDELIM */
