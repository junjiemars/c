#include "flight.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define SHELL_MAX_SIZE              512


static struct message_s message;

static enum flight_op shell(void);
static void zero_tail(char * const);

int
main (int argc, char **argv) {
  if (argc < 2) {
    LOG("where the host?\n");
    exit(EXIT_FAILURE);
  }
  const char *host = argv[1];
  struct addrinfo hints;
  memset(&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  struct addrinfo *addr;
  int s; 
  if (0 != (s = getaddrinfo(host, SERVER_PORT, &hints, &addr))) {
    LOG("!panic: %s\n", gai_strerror(s));
    exit(s);
  }

  LOG("#connect to %s ...\n", host);
  int sock_fd;
  struct addrinfo *ap;

  for (ap = addr; ap; ap = ap->ai_next) {
    sock_fd = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
    if (EOF == sock_fd) {
      LOGX();
      continue;
    }

    if (EOF == connect(sock_fd, ap->ai_addr, ap->ai_addrlen)) {
      LOGX();
      if (EOF == close (sock_fd)) {
        LOGX();
      }
      continue;
    }
    break;
  }

  freeaddrinfo(addr);
  if (!ap) {
    LOG("!panic: no host connectable\n");
    exit(EXIT_FAILURE);
  }
  LOG("#connected\n");

  int op;
  while (1) {
    if (FLIGHT_QUIT == (op = shell())) {
      LOG("#quit ...\n");
      break;
    }

    hton_message(&message);
    if (EOF == send(sock_fd, &message, sizeof(message), MSG_NOSIGNAL)) {
      LOGX();
      exit(errno);
    }

    if (EOF == (recv(sock_fd, &message, sizeof(message), 0))) {
      LOGX();
      exit(errno);
    }
    ntoh_message(&message);

    switch (message.id) {
    case FLIGHT_QUERY: 
    case FLIGHT_STORE:
      LOGM(message.id, message.departure, message.ctime);
      break;
    /* case FE_NO_FOUND: */
    /*   LOG("#response: %s\n", flight_errno_desc(FE_NO_FOUND)); */
    /*   break; */
    /* case FE_OK: */
    /*   LOG("#response: %s\n", flight_errno_desc(FE_OK)); */
    /*   break; */
    default:
      LOG("!panic: unknown error\n");
      break;
    }
  }

  exit (EXIT_SUCCESS);
}

void
zero_tail(char * const buf) {
  size_t len = strnlen(buf, SHELL_MAX_SIZE);
  if ('\n' == buf[len - 1]) {
    buf[len - 1] = '\0';
  }
}

enum flight_op
shell(void) {
  static char inbuf[SHELL_MAX_SIZE];
  int choose;

  while (1) {
    LOG("Flight Info\n");
    LOG("  flight time query  1\n");
    LOG("  store flight time  2\n");
    LOG("  quit               0\n");
    LOG("Choose: ");
    if (!fgets(inbuf, sizeof(inbuf), stdin)) {
      LOGX();
      exit(errno);
    }
    sscanf(inbuf, "%d", &choose);
    enum flight_op op = (enum flight_op)choose;
    memset(&message, 0, sizeof(message));
    message.id = op;
    
    switch (op) {

    case FLIGHT_QUERY:
      {
        LOG("Flight No: ");
        if (!fgets(inbuf, sizeof(inbuf), stdin)) {
          LOGX();
          exit(errno);
        }
        zero_tail(inbuf);
        strcpy(message.flight_no, inbuf);
      }
      break;

    case FLIGHT_STORE:
      {
        while (1) {
          LOG("Flight No: ");
          if (!fgets(inbuf, sizeof(inbuf), stdin)) {
            LOGX();
            exit(errno);
          }
          char *const fno = strstrip(inbuf);
          if (strlen(fno) > 0) {
            zero_tail(fno);
            strncpy(message.flight_no, fno, FLIGHT_NUM_SIZE);
            break;
          }
          if (ferror(stdin)) {
            clearerr(stdin);
          }
          LOG("!panic: invalid input: '%s'\n", inbuf);
        }

        while (1) {
          LOG("A(rrival)/D(eparture): ");
          if (!fgets(inbuf, sizeof(inbuf), stdin)) {
            LOGX();
            exit(errno);
          }

          char ad;
          int read_ad = sscanf(inbuf, " %c", &ad);
          if ((read_ad > 0) && check_departure(ad)) {
            message.departure = toupper(ad);
            break;
          }
          if (ferror(stdin)) {
            clearerr(stdin);
          }
          LOG("!panic: invalid input: '%s'\n", inbuf);
        }

        while (1) {
          LOG("Date (MM/dd/yyyy hh:mm:ss): ");
          if (!fgets(inbuf, sizeof(inbuf), stdin)) {
            LOGX();
            exit(errno);
          }
          zero_tail(inbuf);

          struct tm time;
          int read_time = sscanf(inbuf, "%d/%d/%d %d:%d:%d",
                                 &time.tm_mon,
                                 &time.tm_mday,
                                 &time.tm_year,
                                 &time.tm_hour,
                                 &time.tm_min,
                                 &time.tm_sec);
          if (read_time > 0) {
            time_t epoch = mktime(&time);
            if ((time_t)EOF != epoch) {
              message.epoch = htonl(epoch);
              break;
            }
            LOGX();
          }
          if (ferror(stdin)) {
            clearerr(stdin);
          }
          LOG("!panic: invalid input: '%s'\n", inbuf);
        }
      }
      break;

    case FLIGHT_QUIT:
      break;

    default:
      LOG("!panic: illegal choose, try again\n");
      continue;
    }

    return op;
  }
}
