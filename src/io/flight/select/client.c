#include "flight.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>

#define SHELL_MAX_SIZE              512

#define OP_QUIT                       0
#define OP_QUERY                      1
#define OP_STORE                      2

static struct message message;

#define ZERO_TIME_FIELDS(m) memset((m)->time_fields, 0, sizeof((m)->time_fields) * TF_MAX)

static enum flight_op shell(void);
static void tail_zero(char * const);
static void set_time_fields(struct message * const);

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
    LOG("!panic, %s\n", gai_strerror(s));
    exit(s);
  }

  int sock_fd;
  struct addrinfo *ap;
  for (ap = addr; ap; ap = ap->ai_next) {
    sock_fd = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
    if (EOF == sock_fd) {
      LOG("!panic, %s\n", strerror(errno));
      continue;
    }

    if (EOF == connect(sock_fd, ap->ai_addr, ap->ai_addrlen)) {
      LOG("!panic, %s\n", strerror(errno));
      if (EOF == close (sock_fd)) {
        LOG("!panic, %s\n", strerror(errno));
      }
      continue;
    }
    break;
  }

  freeaddrinfo(addr);
  if (!ap) {
    LOG("!panic, no host connectable\n");
    exit (EXIT_FAILURE);
  }

  int op;

  while (1) {
    op = shell();
    if (OP_QUIT == op) {
      break;
    }

    if (EOF == send(sock_fd, &message, sizeof(struct message), MSG_NOSIGNAL)) {
      LOG("!panic, %s\n", strerror(errno));
      exit(errno);
    }

    if (EOF == (recv(sock_fd, &message, sizeof(struct message), 0))) {
      LOG("!panic, %s\n", strerror(errno));
      exit(errno);
    }

    switch (ntohl(message.id)) {
    case FLIGHT_TIME_STORED: 
    case FLIGHT_TIME_RESULT:
      LOG("\n#response: \n  %s: %c %s %s\n", message.flight_no, message.departure, 
          message.date, message.time);
      break;
    case FLIGHT_NOT_FOUND:
      LOG("\n#response: flight not found\n");
      break;
    case ERROR_IN_INPUT:
      LOG("\n#!panic, read input failed\n");
      break;
    default:
      LOG("\n!panic, unrecongnized message from server\n");
      break;
    }
  }

  exit (EXIT_SUCCESS);
}

void
tail_zero(char * const buf) {
  size_t len = strnlen(buf, SHELL_MAX_SIZE);
  if ('\n' == buf[len - 1]) {
    buf[len - 1] = '\0';
  }
}

void
set_time_fields(struct message * const msg) {
  if (msg->time_fields[TF_YEAR] > 0) {
    msg->time_field_set |= (1 << TF_YEAR);
  }
  if (msg->time_fields[TF_MONTH] > 0) {
    msg->time_field_set |= (1 << TF_MONTH);
  }
  if (msg->time_fields[TF_DAY] > 0) {
    msg->time_field_set |= (1 << TF_DAY);
  }
  if (msg->time_fields[TF_HOUR] > 0) {
    msg->time_field_set |= (1 << TF_HOUR);
  }
  if (msg->time_fields[TF_MINUS] > 0) {
    msg->time_field_set |= (1 << TF_MINUS);
  }
}

enum flight_op
shell(void) {
  static char inbuf[SHELL_MAX_SIZE];
  int choose;

  while (1) {
    printf("flight info\n");
    printf("  flight time query  1\n");
    printf("  store flight time  2\n");
    printf("  quit               0\n");
    printf("choose: ");
    if (!fgets(inbuf, sizeof(inbuf), stdin)) {
      LOG("!panic, %s\n", strerror(errno));
      exit(errno);
    }
    sscanf(inbuf, "%d", &choose);
    enum flight_op op = (enum flight_op)choose;

    switch (op) {

    case FLIGHT_QUERY:
      {
        message.id = htonl(op);
        printf ("flight no: ");
        if (!fgets(inbuf, sizeof(inbuf), stdin)) {
          LOG("!panic, %s\n", strerror(errno));
          exit(errno);
        }
        tail_zero(inbuf);
        strcpy(message.flight_no, inbuf);
      }
      break;

    case FLIGHT_STORE:
      {
        message.id = htonl(op);
        printf("flight no: ");
        if (!fgets(inbuf, sizeof(inbuf), stdin)) {
          LOG("!panic, %s\n", strerror(errno));
          exit(errno);
        }
        tail_zero(inbuf);
        strcpy(message.flight_no, inbuf);

        while (1) {
          printf("A/D: ");
          if (!fgets(inbuf, sizeof(inbuf), stdin)) {
            LOG("!panic, %s\n", strerror(errno));
            exit(errno);
          }

          inbuf[0] = toupper(inbuf[0]);
          if ((inbuf[0] == 'A') || (inbuf[0] == 'D')) {
            message.departure = inbuf[0];
            break;
          }
          LOG("!panic, invalid input: '%s'\n", inbuf);
        }

        int read_time = 0;
        while (1) {
          printf("date (mm/dd/yyyy hh:mm): ");
          if (!fgets(inbuf, sizeof(inbuf), stdin)) {
            LOG("!panic, %s\n", strerror(errno));
            exit(errno);
          }
          ZERO_TIME_FIELDS(&message);
          read_time = sscanf(inbuf, "%hd/%hd/%hd %hd:%hd",
                             &message.time_fields[TF_MONTH],
                             &message.time_fields[TF_DAY],
                             &message.time_fields[TF_YEAR],
                             &message.time_fields[TF_HOUR],
                             &message.time_fields[TF_MINUS]);
          if (read_time) {
            set_time_fields(&message);
            break;
          }
          LOG("!panic, %s\n", strerror(errno));
        }
      }
      break;

    case FLIGHT_QUIT:
      break;

    default:
      LOG("!panic, illegal choose, try again\n");
      continue;
    }

    return op;
  }
}
