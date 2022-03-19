#ifndef _NIO_H_
#define _NIO_H_


#include <npstd.h>


#define NM_MAXLINE  4096


#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#include <stdio.h>



#if !(NM_HAVE_GETDELIM)
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
      *n = NM_MAXLINE;
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


#if !(NM_HAVE_FILENO)
#  error "fileno no found"
#else
#  if (MSVC)
#    define fileno  _fileno
#  endif
#endif  /* !NM_HAVE_FILENO */


#endif /* end of _NIO_H_ */
