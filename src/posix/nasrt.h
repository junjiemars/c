#ifndef _NASRT_H_
#define _NASRT_H_


#include <assert.h>


#if !(NM_HAVE_STATIC_ASSERT)
#  ifdef static_assert
#    undef static_assert
#  endif
#  define static_assert(e, m) enum {static_assert = 1/!!((e) && (m))}

#endif  /* NM_HAVE_STATIC_ASSERT */



#endif /* end of _NASRT_H_ */
