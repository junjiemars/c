
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
#define close closesocket
#define __sendto(s, buf, len, flags, dst, dst_len)                  \
  sendto(s, (const char*) buf, (int) len, flags, (SOCKADDR *) dst,  \
         dst_len)
#define __recvfrom(s, buf, len, flags, dst, dst_len)            \
  recvfrom(s, (char *) buf, (int) len, flags, (SOCKADDR *) dst, \
           dst_len)

#else

typedef int sockfd_t;
#define __sendto(s, buf, len, flags, dst, dst_len)                \
  sendto(s, buf, len, flags, (const struct sockaddr *) dst, dst_len)
#define __recvfrom(s, buf, len, flags, dst, dst_len) \
  recvfrom(s, buf, len, flags, (struct sockaddr *) dst, dst_len)
#endif


#if (MSVC)
/* #pragma warning(disable:4057) */
/* #pragma warning(disable:4214) */
#pragma warning(disable:4244)
/* #pragma warning(disable:4267) */
#pragma warning(disable:4996)

#ifndef ssize_t
#  ifdef  _WIN64
     typedef unsigned __int64 ssize_t;
#  else
     typedef _W64 unsigned int ssize_t;
#  endif
#endif  /* ssize_t */

#define __declare_packed_struct __declspec(align(1)) struct
#define sock_strerror(x) WSAGetLastError()

#else

#define __declare_packed_struct struct __attribute__((packed))
#define sock_strerror(x) strerror(x)

#endif


#ifdef countof
#  undef countof
#endif
#define countof(a) sizeof((a))/sizeof(*(a))


#define _unused_(x) (void)(x)


#endif /* end of _NET_H_ */
