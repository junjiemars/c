#ifndef _NINT_H_
#define _NINT_H_

#include <nore.h>


#if !defined(NM_HAVE_STDINT_H)
#  error "<stdint.h> no found"
#endif


#include <stdint.h>


#if (NM_HAVE_SSIZE_T)
#  if (MSVC)
#    include <BaseTsd.h>
typedef SSIZE_T ssize_t
#  else
#    include <sys/types.h>
#  endif
#else
typedef long ssize_t
#endif


#endif /* end of _NINT_H_ */
