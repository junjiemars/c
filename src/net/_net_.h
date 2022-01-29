#ifndef _NET_H_
#define _NET_H_

#include <nore.h>
#include <ndef.h>
#include <nint.h>
#include <nstr.h>


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


#if (MSVC)
typedef SOCKET sockfd_t;
#define close closesocket
#define __sendto(s, buf, len, flags, dst, dst_len)                  \
  sendto(s, (const char*) buf, (int) len, flags, (SOCKADDR *) dst,  \
         dst_len)
#define __recvfrom(s, buf, len, flags, dst, dst_len)            \
  recvfrom(s, (char *) buf, (int) len, flags, (SOCKADDR *) dst, \
           dst_len)
#define log_sockerr(r, s)                                               \
  do                                                                    \
    {                                                                   \
      char buf[256];                                                    \
      DWORD flags;                                                      \
      flags = FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS; \
      r = WSAGetLastError();                                            \
      buf[0] = 0;                                                       \
      FormatMessage(flags, NULL, r, 0, buf, sizeof(buf), NULL);         \
      fprintf(stderr, (s), buf);                                        \
    } while (0)

#else

typedef int sockfd_t;
#define __sendto(s, buf, len, flags, dst, dst_len)                \
  sendto(s, buf, len, flags, (const struct sockaddr *) dst, dst_len)
#define __recvfrom(s, buf, len, flags, dst, dst_len) \
  recvfrom(s, buf, len, flags, (struct sockaddr *) dst, dst_len)
#define log_sockerr(r, s)                       \
  do                                            \
    {                                           \
      r = errno;                                \
      fprintf(stderr, (s), strerror(r));        \
    } while (0)

#endif  /* MSVC */


#if (MSVC)
#pragma warning(disable:4244)
#pragma warning(disable:4996)
#else
#endif  /* MSVC */


#ifdef countof
#  undef countof
#endif
#define countof(a)  (sizeof(a)/sizeof(*(a)))



#endif /* end of _NET_H_ */
