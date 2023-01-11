#ifndef _NLIM_H_
#define _NLIM_H_


#include <nustd.h>
#include <limits.h>


#if (MSVC)
#  if !defined(SSIZE_MAX)
#    define SSIZE_MAX  LONG_MAX
#  endif
#endif  /* SSIZE_MAX */



#if (NM_HAVE_TIMES)
#include <sys/times.h>
#define _times_(E, R, U, S)                           \
do                                                    \
{                                                     \
  clock_t s, e;                                       \
  struct tms st, et;                                  \
  s = times(&st);                                     \
  (E);                                                \
  e = times(&et);                                     \
  R = (e-s)/(double)NM_CLK_TCK;                       \
  U = (et.tms_utime-st.tms_utime)/(double)NM_CLK_TCK; \
  S = (et.tms_stime-st.tms_stime)/(double)NM_CLK_TCK; \
} while (0)
#endif  /* _times_ */



#endif /* end of _NLIM_H_ */
