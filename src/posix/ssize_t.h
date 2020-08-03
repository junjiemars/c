#ifndef _SSIZE_T_H_
#define _SSIZE_T_H_

#if (MSVC)
#  include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#  include <sys/types.h>
#endif


#endif /* end of _SSIZE_T_H_ */
