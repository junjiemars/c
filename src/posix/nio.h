#ifndef _NIO_H_
#define _NIO_H_


#include <nustd.h>
#include <nlim.h>
#include <stdio.h>


#if (MSVC)
#  pragma warning(disable: 4996)  /* _CRT_SECURE_NO_WARNINGS */
#endif


#if !(NM_HAVE_GETDELIM)
ssize_t getdelim(char ** restrict lineptr, size_t * restrict n, int delimiter,
                 FILE * restrict stream);
#  if defined(getline)
#    undef getline
#  endif
#  define getline(lp, n, f)  getdelim((lp), (n), 0x0a, (f))
#endif  /* getdelim */


#if (MSVC) && (NM_HAVE_FILENO)
#  define fileno  _fileno
#endif  /* fileno */


#if (MSVC) && (NM_HAVE_FDOPEN)
#  define fdopen  _fdopen
#endif  /* fdopen */


#if (NM_HAVE_DIRNAME_GETFULLPATHNAME || NM_HAVE_BASENAME_GETFULLPATHNAME)
char *_libgen_(char *, int);
#  if defined(dirname)
#    undef dirname
#  endif
#  define dirname(p)  _libgen_((p), 1)
#  if defined(basename)
#    undef basename
#  endif
#  define basename(p)  _libgen_((p), 0)
#elif (NM_HAVE_DIRNAME || NM_HAVE_BASENAME)
#  include <libgen.h>
#endif  /* dirname, basename */


#if (MSVC) && (NM_HAVE_POPEN)
#  ifdef popen
#    undef popen
#    undef pclose
#  endif
#  define popen  _popen
#  define pclose _pclose
#endif  /* popen */


#endif /* end of _NIO_H_ */
