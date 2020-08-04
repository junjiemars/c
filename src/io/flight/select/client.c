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

#define OP_QUIT                       0
#define OP_QUERY                      1
#define OP_STORE                      2

static struct message message;
static char inbuf[512];

static int get_input (void);

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
    op = get_input();
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

    switch (ntohl (message.message_id)) {
    case FLIGHT_TIME_STORED: 
    case FLIGHT_TIME_RESULT:
      LOG("\n#response: \n  %s: %s %s %s\n", message.flight_no, message.departure, 
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

int
get_input (void) {
  int option;

  while (1) {
    printf ("Flight Info\n\n");
    printf ("\tFlight time query\t1\n");
    printf ("\tStore flight time\t2\n");
    printf ("\tQuit\t\t0\n\n");
    printf ("Your option: ");
    if (!fgets(inbuf, sizeof (inbuf), stdin)) {
      LOG("!panic, %s\n", strerror(errno));
      exit(errno);
    }
    sscanf(inbuf, "%d", &option);

    int len;

    switch (option) {

    case 1: message.message_id = htonl (FLIGHT_TIME);
      printf ("Flight no: ");
      if (!fgets(inbuf, sizeof(inbuf), stdin)) {
        LOG("!panic, %s\n", strerror(errno));
        exit(errno);
      }
      len = strlen (inbuf);
      if (inbuf [len - 1] == '\n')
        inbuf [len - 1] = '\0';
      strcpy (message.flight_no, inbuf);
      break;

    case 2: message.message_id = htonl (STORE_FLIGHT);
      printf ("Flight no: ");
      if (!fgets(inbuf, sizeof(inbuf), stdin)) {
        LOG("!panic, %s\n", strerror(errno));
        exit(errno);
      }
      len = strlen (inbuf);
      if (inbuf [len - 1] == '\n')
        inbuf [len - 1] = '\0';
      strcpy (message.flight_no, inbuf);

      while (1) {
        printf ("A/D: ");
        if (fgets(inbuf, sizeof(inbuf), stdin)) {
          LOG("!panic, %s\n", strerror(errno));
          exit(errno);
        }
        message.departure [0] = toupper (inbuf [0]);
        message.departure [1] = '\0';
        if ((message.departure [0] == 'A') || (message.departure [0] == 'D'))
          break;
        printf ("Error in input, valid values are A and D\n");
      }
                    
      printf ("date (dd/mm/yyyy): ");
      if (!fgets(inbuf, sizeof(inbuf), stdin)) {
        LOG("!panic, %s\n", strerror(errno));
        exit(errno);
      }
      strncpy (message.date, inbuf, 10);
      message.date [10] = '\0';
      printf ("time (hh:mm): ");
      if (!fgets(inbuf, sizeof(inbuf), stdin)) {
        LOG("!panic, %s\n", strerror(errno));
        exit(errno);
      }
      strncpy (message.time, inbuf, 5);
      message.time [5] = '\0';
      break;

    case 0:
      break;

    default: printf ("Illegal option, try again\n\n");
      continue;

    }

    return option;
  }
}
