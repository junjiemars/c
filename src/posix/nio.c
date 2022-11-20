#include <nio.h>


/*
 * 1. `getdelim(3)': conform to IEEE Std 1003.1-2017
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html
 *
 * 2. `dirname(3)'.
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/dirname.html
 *
 * 3. `basename(3)'.
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/basename.html
 *
 *
*/

#if !(NM_HAVE_GETDELIM)

#include <errno.h>
#include <limits.h>
#include <stdio.h>
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

  if (NULL == *lineptr)
    {
      if (0 == *n)
        {
          *n = NM_LINE_MAX;
        }

      *lineptr = malloc(*n);
      if (NULL == *lineptr)
        {
          return EOF;
        }
    }

  p = *lineptr;
  len = 0;

  while (EOF != (c = fgetc(stream)))
    {
      if (SSIZE_MAX == (ssize_t) len)
        {
          errno = EOVERFLOW;
          return EOF;
        }

      if ((*n - 1) == (size_t) len)
        {
          *n <<= 1;
          p1 = realloc(*lineptr, *n);
          if (NULL == p1)
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


#if (NM_HAVE_DIRNAME_GETFULLPATHNAME) || (NM_HAVE_BASENAME_GETFULLPATHNAME)
#include <windows.h>
#include <tchar.h>
#include <string.h>

static char *
_getfullpathname_(char *path, int dir)
{
  static TCHAR d[NM_PATH_MAX + 1], *b;

  if (path == NULL || strcmp(path, "") == 0)
    {
      d[0] = '.';
      d[1] = 0;
      return d;
    }

  if (0 == GetFullPathName(path, _nof_(d), d, &b))
    {
      return 0;
    }

  if (dir)
    {
      b[-1] = 0; /* remove '/basename' part */
      return d;
    }
  else
    {
      return b;
    }
}

char *
dirname(char *path)
{
  return _getfullpathname_(path, 1);
}

char *
basename(char *path)
{
  return _getfullpathname_(path, 0);
}

#endif  /* dirname, basename */
