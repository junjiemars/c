#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <nore.h>

#if (GCC)
#  if defined(_GNU_SOURCE)
#    undef _GNU_SOURCE
#  endif  /* _GNU_SOURCE */
#
#  if defined(_POSIX_C_SOURCE)
#    undef _POSIX_C_SOURCE
#  endif  /* _POSIX_C_SOURCE */
#  define _POSIX_C_SOURCE 200112L
#
#  if !defined(_DEFAULT_SOURCE)
#    define _DEFAULT_SOURCE
#  endif
#endif  /* GCC */


#include <ndef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#endif /* end of _PROCESS_H_ */
