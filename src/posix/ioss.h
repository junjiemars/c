#ifndef _IOSS_H_
#define _IOSS_H_


#include <nore.h>


#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#if (LINUX)
#  if !defined(__USE_POSIX)
#    define __USE_POSIX
#  endif
#endif  /* fileno */


#if (LINUX)
#  if !defined(_GNU_SOURCE)
#    define __USE_XOPEN2K8
#  endif
#endif  /* getline */


#include <stdio.h>



#if !(NM_HAVE_GETLINE)
#  ifndef GETLINE_LINE_MAX
#    define GETLINE_LINE_MAX  512
#  endif
#  include <defs.h>
#  include <ints.h>
#  include <stdlib.h>

ssize_t
getline(char ** restrict lineptr, size_t * restrict n, FILE * restrict stream)
{
	int       c;
	ssize_t   line_len;
	char     *p, *p1;

  if (0 == lineptr)
    {
      return EOF;
    }
	if (0 == *lineptr && 0 == *n)
    {
      *n = GETLINE_LINE_MAX;
      *lineptr = malloc(*n);
      if (0 == *lineptr)
        {
          return EOF;
        }
    }
  p = *lineptr;

	while (EOF != (c = fgetc(stream)))
    {
      if ((size_t) line_len == (*n - 1))
        {
          *n <<= 1;
          p1 = realloc(*lineptr, *n);
          if (0 == p1)
            {
              return EOF;
            }
          *lineptr = p1;
          p = p1 + line_len;
        }
      *p++ = c;
      line_len++;

      if ('\n' == c)
        {
          *p = 0;
          return line_len;
        }
    }

	return line_len;
}
#endif  /* end of getline */


#endif /* end of _IOSS_H_ */
