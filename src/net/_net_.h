
#ifndef _NET_H_
#define _NET_H_

#include <nore.h>

#if WINNT
# include <winsock2.h>
# include <ws2tcpip.h>
# pragma comment (lib, "Ws2_32.lib")
#else
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <unistd.h>
#endif


#ifdef NM_HAVE_STDINT_H
# include <stdint.h>
#else
# include <stddef.h>
  typedef __int8 int8_t;
  typedef unsigned __int8 uint8_t;
  typedef __int16 int16_t;
  typedef unsigned __int16 uint16_t;
  typedef __int32 int32_t;
  typedef unsigned __int32 uint32_t;
  typedef __int64 int64_t;
  typedef unsigned __int64 uint64_t;
#endif

#if WINNT
  typedef SOCKET sock_t;
# define close closesocket
#else
  typedef int sock_t;
#endif

#if MSVC
# pragma warning(disable:4214)
# pragma warning(disable:4996)
#endif

#define _unused_(x) (void)(x)


#endif /* end of _NET_H_ */
