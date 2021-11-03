
#ifndef _NET_H_
#define _NET_H_

#include <nore.h>

#if (WINNT)
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  include <windows.h>
#  include <process.h>
#  pragma comment (lib, "Ws2_32.lib")
#  pragma comment (lib, "Mswsock.lib")
#  pragma comment (lib, "AdvApi32.lib")
#  define getpid  GetCurrentProcessId
#else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netdb.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#endif


#include <stddef.h>
#if (MSVC)
#  include <BaseTsd.h>
   typedef __int8 int8_t;
   typedef unsigned __int8 uint8_t;
   typedef __int16 int16_t;
   typedef unsigned __int16 uint16_t;
   typedef __int32 int32_t;
   typedef unsigned __int32 uint32_t;
   typedef __int64 int64_t;
   typedef unsigned __int64 uint64_t;
   typedef SSIZE_T  ssize_t;
#else
#  include <stdint.h>
#endif


#if (MSVC)
typedef SOCKET sockfd_t;
#define close closesocket
#define __sendto(s, buf, len, flags, dst, dst_len)                  \
  sendto(s, (const char*) buf, (int) len, flags, (SOCKADDR *) dst,  \
         dst_len)
#define __recvfrom(s, buf, len, flags, dst, dst_len)            \
  recvfrom(s, (char *) buf, (int) len, flags, (SOCKADDR *) dst, \
           dst_len)
#define log_sock_err(s)                                                 \
  do                                                                    \
    {                                                                   \
      int e;                                                            \
      char buf[256];                                                    \
      DWORD flags;                                                      \
      flags = FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS; \
      e = WSAGetLastError();                                            \
      buf[0] = 0;                                                       \
      FormatMessage(flags, NULL, e, 0, buf, sizeof(buf), NULL);         \
      fprintf(stderr, (s), buf);                                        \
    } while (0)

#else

typedef int sockfd_t;
#define __sendto(s, buf, len, flags, dst, dst_len)                \
  sendto(s, buf, len, flags, (const struct sockaddr *) dst, dst_len)
#define __recvfrom(s, buf, len, flags, dst, dst_len) \
  recvfrom(s, buf, len, flags, (struct sockaddr *) dst, dst_len)
#define log_sock_err(s)  fprintf(stderr, (s), strerror(errno))

#endif  /* MSVC */


#if (MSVC)
#pragma warning(disable:4244)
#pragma warning(disable:4996)

#define __declare_packed_struct struct

#else

#define __declare_packed_struct struct __attribute__((packed))

#endif  /* MSVC */


#ifdef countof
#  undef countof
#endif
#define countof(a) (sizeof(a)/sizeof(*(a)))


#define _unused_(x) (void)(x)


#endif /* end of _NET_H_ */
