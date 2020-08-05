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

      if (FD_ISSET(reqs[i], &r_fds)) {
        struct message_s in;
        ssize_t recved = recv(reqs[i], &in, sizeof(in), 0);
        if (EOF == recved) {
          LOGX();
        } else if (recved != sizeof(in)) {
          LOG("!panic: read failed, %zu/%zu\n", sizeof(in), recved);
        }
        ntoh_message(&in);
        ctime_r(&in.epoch, &in.ctime[0]);
        LOGM(in.id, in.departure, in.ctime);
      }
      LOG("#---\n");
    }
        
    /* for (int fd = 0; fd < (fdmax + 1); fd++) { */
    /*   if (FD_ISSET (fd, &r_fds)) { */
    /*     if (fd == s_listen) { */
    /*       addrlen = sizeof (struct sockaddr_storage); */
    /*       int fd_new; */
    /*       if ((fd_new = accept (s_listen, (struct sockaddr *) &client_saddr, &addrlen)) == -1) */
    /*         error ("accept"); */
    /*       FD_SET (fd_new, &fds);  */
    /*       if (fd_new > fdmax)  */
    /*         fdmax = fd_new; */

    /*       // print IP address of the new client */
    /*       if (client_saddr.ss_family == AF_INET) { */
    /*         ptr = (struct sockaddr_in *) &client_saddr; */
    /*         inet_ntop (AF_INET, &(ptr -> sin_addr), str, sizeof (str)); */
    /*       } */
    /*       else if (client_saddr.ss_family == AF_INET6) { */
    /*         ptr1 = (struct sockaddr_in6 *) &client_saddr; */
    /*         inet_ntop (AF_INET6, &(ptr1 -> sin6_addr), str, sizeof (str)); */
    /*       } */
    /*       else */
    /*         { */
    /*           ptr = NULL; */
    /*           fprintf (stderr, "Address family is neither AF_INET nor AF_INET6\n"); */
    /*         } */
    /*       if (ptr) { */
    /*         /\* !TODO: *\/ */
    /*       } */
                
    /*     } */
    /*     else */
    /*       { */
    /*         struct message_s in; */
    /*         memset(&in, 0, sizeof(in)); */
    /*         ssize_t numbytes = recv(fd, &in, sizeof(in), 0); */
   
    /*         if (numbytes == -1) */
    /*           error ("recv"); */
    /*         else if (numbytes == 0) { */
    /*           // connection closed by client */
    /*           fprintf (stderr, "Socket %d closed by client\n", fd); */
    /*           if (close (fd) == -1) */
    /*             error ("close"); */
    /*           FD_CLR (fd, &fds); */
    /*         } */
    /*         else  */
    /*           { */
    /*             // data from client */
    /*             bool valid; */
    /*             char temp_buf [FLIGHT_NUM_SIZE + 1]; */
                        
    /*             switch (ntohl (in.id)) { */
    /*             case STORE_FLIGHT: */
    /*               valid = true; */
    /*               // validate flight number */
    /*               if (in.flight_no [FLIGHT_NUM_SIZE]) */
    /*                 in.flight_no [FLIGHT_NUM_SIZE] = '\0'; */
    /*               if (strlen (in.flight_no) < 3) */
    /*                 valid = false; */
    /*               trim (temp_buf, in.flight_no); */
    /*               strcpy (in.flight_no, temp_buf); */
    /*               bool departure; */
    /*               if (toupper (in.departure) == 'D') */
    /*                 departure = true; */
    /*               else if (toupper (in.departure) == 'A') */
    /*                 departure = false;  */
    /*               else */
    /*                 valid = false; */

    /*               char delim [] = "/"; */
    /*               char *mday, *month, *year, *saveptr; */
    /*               mday = month = year = NULL; */
    /*               mday = strtok_r (in.date, delim, &saveptr); */
    /*               if (mday) */
    /*                 month = strtok_r (NULL, delim, &saveptr); */
    /*               else  */
    /*                 valid = false; */
    /*               if (month) */
    /*                 year = strtok_r (NULL, delim, &saveptr); */
    /*               else  */
    /*                 valid = false; */
    /*               if (!year) */
    /*                 valid = false; */
    /*               char *hrs, *min; */
    /*               // get time */
    /*               if (in.time [5]) */
    /*                 in.time [5] = '\0'; */
    /*               delim [0] = ':'; */
    /*               hrs = min = NULL; */
    /*               hrs = strtok_r (in.time, delim, &saveptr); */
    /*               if (hrs)  */
    /*                 min = strtok_r (NULL, delim, &saveptr); */
    /*               if (!hrs || !min) */
    /*                 valid = false; */

    /*               time_t ts; */

    /*               if (valid) { */
    /*                 struct tm tm; */

    /*                 tm.tm_sec = 0; */
    /*                 sscanf (min, "%d", &tm.tm_min); */
    /*                 sscanf (hrs, "%d", &tm.tm_hour); */
    /*                 sscanf (mday, "%d", &tm.tm_mday); */
    /*                 sscanf (month, "%d", &tm.tm_mon); */
    /*                 (tm.tm_mon)--; */
    /*                 sscanf (year, "%d", &tm.tm_year); */
    /*                 tm.tm_year -= 1900; */
    /*                 tm.tm_isdst = -1; */

    /*                 if ((ts = mktime (&tm)) == (time_t) -1) */
    /*                   valid = false; */
                                  
    /*                 time_t now; */

    /*                 if ((now = time (NULL)) == (time_t) -1) */
    /*                   error ("time"); */

    /*                 if (ts < now) */
    /*                   valid = false; */
    /*               } */

    /*               if (!valid) { */
    /*                 // send error message to client */
    /*                 send_message.id = htonl (ERROR_IN_INPUT); */
    /*                 size_t msg_len = sizeof (long); */
    /*                 if (send (fd, &send_message, msg_len, 0) == -1) */
    /*                   error ("send"); */
    /*               } */
    /*               else */
    /*                 { */
    /*                   // add flight data to tree */
    /*                   root = add_to_tree (root, in.flight_no, departure, ts); */
    /*                   // send confirmation to client */
    /*                   send_message.id = htonl (FLIGHT_TIME_STORED); */
    /*                   strcpy(send_message.flight_no, in.flight_no); */
    /*                   send_message.departure = (departure) ? 'D' : 'A'; */
    /*                   struct tm *tms;   */
    /*                   if ((tms = localtime (&ts)) == NULL)   */
    /*                     perror ("localtime");                     */
    /*                   sprintf (send_message.date, "%02d/%02d/%d", tms -> tm_mday,  */
    /*                            tms -> tm_mon + 1, tms -> tm_year + 1900); */
    /*                   sprintf (send_message.time, "%02d:%02d", tms -> tm_hour, */
    /*                            tms -> tm_min); */
    /*                   size_t msg_len = sizeof (struct message_s); */
    /*                   if (send (fd, &send_message, msg_len, 0) == -1) */
    /*                     error ("send"); */
    /*                 } */
    /*               break; */
    /*             case FLIGHT_TIME: */
    /*               valid = true; */
    /*               // validate flight number */
    /*               if (in.flight_no [FLIGHT_NUM_SIZE]) */
    /*                 in.flight_no [FLIGHT_NUM_SIZE] = '\0'; */
    /*               if (strlen (in.flight_no) < 3) */
    /*                 valid = false; */
    /*               if (!valid) { */
    /*                 // send error message to client */
    /*                 send_message.id = htonl (ERROR_IN_INPUT); */
    /*                 size_t msg_len = sizeof (long); */
    /*                 if (send (fd, &send_message, msg_len, 0) == -1) */
    /*                   error ("send"); */
    /*                 break; */
    /*               } */
    /*               char temp_buf [FLIGHT_NUM_SIZE + 1]; */
    /*               trim (temp_buf, in.flight_no); */
    /*               strcpy (in.flight_no, temp_buf); */
    /*               struct tnode *ptr; */
    /*               ptr = find_flight_rec (root, in.flight_no); */
    /*               if (!ptr) { */
    /*                 memset (&send_message, '\0', sizeof (struct message_s)); */
    /*                 send_message.id = htonl (FLIGHT_NOT_FOUND); */
    /*                 strcpy (send_message.flight_no, in.flight_no); */
    /*                 size_t msg_len = sizeof (struct message_s); */
    /*                 if (send (fd, &send_message, msg_len, 0) == -1) */
    /*                   error ("send"); */
    /*                 break; */
    /*               } */
    /*               send_message.id = htonl (FLIGHT_TIME_RESULT); */
    /*               strcpy (send_message.flight_no, in.flight_no); */
    /*               send_message.departure = (ptr->departure) ? 'D' : 'A'; */
    /*               struct tm *tms;   */
    /*               if ((tms = localtime (&(ptr -> flight_time))) == NULL)   */
    /*                 perror ("localtime");                     */
    /*               sprintf (send_message.date, "%02d/%02d/%d", tms -> tm_mday,  */
    /*                        tms -> tm_mon + 1, tms -> tm_year + 1900); */
    /*               sprintf (send_message.time, "%02d:%02d", tms -> tm_hour, */
    /*                        tms -> tm_min); */
    /*               size_t msg_len = sizeof (struct message_s); */
    /*               if (send (fd, &send_message, msg_len, 0) == -1) */
    /*                 error ("send"); */
    /*               break; */

    /*             } */

    /*           } */
    /*       } */
    /*   } // if (fd == ... */
    /* } // for */
  } // while (1)  
}
