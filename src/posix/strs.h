#ifndef _STRS_H_
#define _STRS_H_

#if (WINNT) && (MSVC)
#  define strerror_r(errno, buf, len) strerror_s(buf, len, errno)
#  define strtok_r                    strtok_s
#endif

#endif /* end of _STRS_H_ */

