#ifndef _NIO_H_
#define _NIO_H_


#include <nustd.h>
#include <nlim.h>


#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#include <stdio.h>



#if !(NM_HAVE_GETDELIM)

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
#endif  /* fileno */


#if !defined(_fpos_)
#  if (LINUX)
#    define _fpos_(x)  x.__pos
#  else
#    define _fpos_(x)  x
#  endif
#endif


#endif /* end of _NIO_H_ */
