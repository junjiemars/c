#ifndef _IPC_H_
#define _IPC_H_

#include <nustd.h>
#include <nlim.h>
#include <nstr.h>
#include <nio.h>
#include <nasrt.h>
#include <errno.h>
#include <stdlib.h>


#if (LINUX)
#  include <sys/wait.h>
#endif

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>


#endif  /* _IPC_H_ */
