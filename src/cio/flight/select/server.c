#include "flight.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/select.h>
#include <ctype.h>
#include <time.h>

#define MAX_REQ            4
#define BACKLOG            8

void run(int);

int
main (int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* stream socket */
  hints.ai_flags = AI_PASSIVE;     /* for wildcard IP address */

  struct addrinfo *addr;
  int s; 
  if (0 != (s = getaddrinfo(0, SERVER_PORT, &hints, &addr))) {
    LOG("!panic, %s\n", gai_strerror(s));
    exit(s);
  }

  int s_listen, s_opt = 1;
  struct addrinfo *ap;
  for (ap = addr; ap; ap = ap->ai_next) {
    s_listen = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
    if (EOF == s_listen) {
      LOG("!panic, %s\n", strerror(errno));
      continue;
    }

    if (EOF == setsockopt(s_listen, SOL_SOCKET, SO_REUSEADDR,
                          &s_opt, sizeof(int))) {
      LOG("!panic, %s\n", strerror(errno));
      exit(errno);
    }

    if (!bind(s_listen, ap->ai_addr, ap->ai_addrlen)) {
      LOG("#binding ...\n");
      break;
    }

    if (EOF == close(s_listen)) {
      LOG("!panic, %s\n", strerror(errno));
      exit(errno);
    }
  }

  freeaddrinfo(addr);
  if (!ap) {
    LOG("!panic, not able to bind\n");
    exit(EXIT_FAILURE);
  }
  LOG("#listening ... \n");

  if (EOF == listen(s_listen, BACKLOG)) {
    LOG("!panic, %s\n", strerror(errno));
    exit(errno);
  }

  run(s_listen);
  exit (EXIT_SUCCESS);
}

void
run(int s_listen) {
  fd_set r_fds;
  int max_fd;
  int reqs[MAX_REQ] = { 0 };

  while (1) {
    FD_ZERO(&r_fds);
    FD_SET(s_listen, &r_fds);
    max_fd = s_listen;

    for (int i = 0; i < MAX_REQ; i++) {
      int fd = reqs[i];
      if (fd > 0) {
        FD_SET(fd, &r_fds);
      }
      if (fd > max_fd) {
        max_fd = fd;
      }
    }

    struct timeval tv;
    tv.tv_sec = 300;
    tv.tv_usec = 0;

    int retval = select(max_fd + 1, &r_fds, 0, 0, &tv);
    if (EOF == retval) {
      LOGX();
    } else if (0 == retval) {
      LOG("!panic: select timeout[%d]\n", (int)tv.tv_sec);
    }

    if (FD_ISSET(s_listen, &r_fds)) {
      struct sockaddr_in req_addr;
      socklen_t req_len;
      int new_fd = accept(s_listen,
                          (struct sockaddr*)&req_addr,
                          (socklen_t*)&req_len);
      if (EOF == new_fd) {
        LOGX();
        exit(errno);
      }

      LOG("#accept, [%d], %s:%d\n",
          new_fd,
          inet_ntoa(req_addr.sin_addr),
          ntohs(req_addr.sin_port));

      for (int i = 0; i < MAX_REQ; i++) {
          if (0 == reqs[i]) {
            reqs[i] = new_fd;
            break;
          }
      }
    }

    for (int i = 0; i < MAX_REQ; i++) {
      if (!FD_ISSET(reqs[i], &r_fds)) {
        continue;
      }

      struct message_s in;
      ssize_t recved = recv(reqs[i], &in, sizeof(in), 0);
      if (EOF == recved) {
        LOGX();
      } else if (recved != sizeof(in)) {
        LOG("!panic: read failed, %zu/%zu\n", sizeof(in), recved);
      }
      ntoh_message(&in);
      ctime_r(&in.epoch, &in.ctime[0]);

      close(reqs[i]);
      reqs[i] = 0;
      
      LOGM(in.id, in.departure, in.ctime);
      LOG("#---\n");
    }
  }
}
