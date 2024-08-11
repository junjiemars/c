#include "_ipc_.h"
#include <stdlib.h>
#include <sys/socket.h>

void pr_addr (const struct sockaddr *, const char *);

int
main (void)
{




  /* unix address */
  struct sockaddr_un unix = { 0 };
  unix.sun_family = AF_UNIX;
  strcpy (unix.sun_path, "sock_addr.file");
  pr_addr ((struct sockaddr *)&unix, "unix");

  /* internet v4 address */
  struct sockaddr_in in4 = { 0 };
  in4.sin_family = AF_INET;
  in4.sin_port = 0x1234;
  in4.sin_addr.s_addr = 0x7f000001;
  pr_addr ((struct sockaddr *)&in4, "in4");

  /* internet v6 address */
  struct sockaddr_in6 in6 = { 0 };
  in6.sin6_family = AF_INET;
  in6.sin6_port = 0x1234;
  struct in6_addr in6_addr = {0};
  in6.sin6_addr = in6_addr;
  pr_addr ((struct sockaddr *)&in6, "in6");

  exit (EXIT_SUCCESS);
}

void
pr_addr (const struct sockaddr *addr, const char *prefix)
{
  printf ("%s -> sockaddr\n------------\n"
          "sa_family = 0x%0x, offset = %lu\n"
          "sa_data = %s, offset = %lu\n",
          prefix, addr->sa_family, offsetof (struct sockaddr, sa_family),
          addr->sa_data, offsetof (struct sockaddr, sa_data));
}
