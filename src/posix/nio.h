#ifndef _NIO_H_
#define _NIO_H_


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
#  if !defined(__USE_XOPEN2K8)
#    define __USE_XOPEN2K8
#  endif
#endif  /* getline */


#include <stdio.h>



#if !(NM_HAVE_GETDELIM)
#  ifndef GETDELIM_LEN_MAX
#    define GETDELIM_LEN_MAX  512
#  endif
#  include <ndef.h>
#  include <nint.h>
#  include <stdlib.h>

ssize_t
getdelim(char ** restrict lineptr, size_t * restrict n, int delimiter,
         FILE * restrict stream)
{
	int       c;
	ssize_t   len;
	char     *p, *p1;

  if (0 == lineptr)
    {
      return EOF;
    }
	if (0 == *lineptr)
    {
      *n = GETDELIM_LEN_MAX;
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

  *++p = 0;
	return len;
}

#  if defined(getline)
#    undef getline
#  endif
#  define getline(lp, n, f)  getdelim((lp), (n), 0x0a, (f))

#endif  /* end of getdelim */


#endif /* end of _NIO_H_ */
