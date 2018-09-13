
#ifndef _NETL_H_
#define _NETL_H_

#include <nore.h>

#if (WINNT)
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

#define _unused_(x) (void)(x)

#endif /* end of _NETL_H_ */
