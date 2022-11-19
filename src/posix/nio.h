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


#if (MSVC) && (NM_HAVE_FILENO)
#  define fileno  _fileno

#endif  /* fileno */


#if (MSVC) && (NM_HAVE_FDOPEN)
#  define fdopen  _fdopen

#endif  /* fdopen */


#if (NM_HAVE_DIRNAME_GETFULLPATHNAME) || (NM_HAVE_BASENAME_GETFULLPATHNAME)
char  *dirname(char *path);
char  *basename(char *path);

#endif  /* dirname, basename */




#endif /* end of _NIO_H_ */
