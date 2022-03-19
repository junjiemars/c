#ifndef _NIO_H_
#define _NIO_H_


#include <npstd.h>


#define NM_MAXLINE  4096


#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#include <stdio.h>



#if !(NM_HAVE_GETDELIM)
#  include <nint.h>
ssize_t getdelim(char ** restrict lineptr, size_t * restrict n, int delimiter,
                 FILE * restrict stream);
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
