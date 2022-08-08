#include <nio.h>

/*
 * An implementation conform to IEEE Std 1003.1-2017:
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html
 *
*/

#if !(NM_HAVE_GETDELIM)

#include <errno.h>
#include <stdlib.h>

ssize_t
getdelim(char **restrict lineptr, size_t *restrict n, int delimiter,
         FILE *restrict stream)
{
  int       c;
  char     *p, *p1;
  ssize_t   len;

  if (NULL == lineptr || NULL == n || NULL == stream
      || (UCHAR_MAX < delimiter || delimiter < 0))
    {
      errno = EINVAL;
      return EOF;
    }

  if (feof(stream) || ferror(stream))
    {
      return EOF;
    }

  if (0 == *lineptr)
    {
      if (0 == *n)
        {
          *n = NM_LINE_MAX;
        }

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

  if (ferror(stream))
    {
      return EOF;
    }

  *p = 0;
  return len;
}

#endif  /* getdelim */
