
#ifndef _NET_H_
#define _NET_H_

#include <nore.h>

#if (WINNT)
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  include <windows.h>
#  include <process.h>
#  pragma comment (lib, "Ws2_32.lib")
#  define getpid  GetCurrentProcessId
#else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netdb.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#endif


#if defined(NM_HAVE_STDINT_H)
#  include <stdint.h>
#else
#  include <stddef.h>
   typedef __int8 int8_t;
   typedef unsigned __int8 uint8_t;
   typedef __int16 int16_t;
   typedef unsigned __int16 uint16_t;
   typedef __int32 int32_t;
   typedef unsigned __int32 uint32_t;
   typedef __int64 int64_t;
   typedef unsigned __int64 uint64_t;
#endif

#if (WINNT)
   typedef SOCKET sockfd_t;
#  define close closesocket
#else
   typedef int sockfd_t;
#endif

/* #if (DARWIN) */
/* #  define _setsockopt_  (void) */
/* #elif (LINUX) */
/* #  define _setsockopt_  setsockopt */
/* #endif */

#if (MSVC)
#  pragma warning(disable:4057)
#  pragma warning(disable:4214)
#  pragma warning(disable:4244)
#  pragma warning(disable:4267)
#  pragma warning(disable:4996)
#  ifndef ssize_t
#    ifdef  _WIN64
       typedef unsigned __int64 ssize_t;
#    else
       typedef _W64 unsigned int ssize_t;
#    endif
#  endif  /* ssize_t */
#endif

#define _unused_(x) (void)(x)


#endif /* end of _NET_H_ */
