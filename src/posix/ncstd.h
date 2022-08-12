/**
 * Nore C standard
 */

#ifndef _NCSTD_H_
#define _NCSTD_H_


#include <ndef.h>
#include <nint.h>
#include <nstr.h>



#if !defined(_fpos_)
#  if (LINUX)
#    define _fpos_(x)  x.__pos
#  else
#    define _fpos_(x)  x
#  endif
#endif



#endif /* _NCSTD_H_ */
