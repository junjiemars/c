#include "_ipc_.h"
#include <netinet/in.h>

void print_addr (const struct sockaddr *, const char *);

int
main (void)
{
  /* unix address */
  struct sockaddr_un unix = { 0 };
  unix.sun_family = AF_UNIX;
  strcpy (unix.sun_path, "sock_addr.file");
  print_addr ((struct sockaddr *)&unix, "unix");

  /* internet v4 address */
  struct sockaddr_in in4 = { 0 };
  in4.sin_family = AF_INET;
  in4.sin_port = 0x1234;
  inet_pton (AF_INET, "127.0.0.1", &in4.sin_addr.s_addr);
  print_addr ((struct sockaddr *)&in4, "in4");


  /* internet v6 address */
  struct sockaddr_in6 in6 = { 0 };
  in6.sin6_family = AF_INET6;
  in6.sin6_port = 0x1234;
  inet_pton (AF_INET6, "240e:3a2:e7f:1410:84eb:7d13:9c3a:e7f5",
             &in6.sin6_addr);
  print_addr ((struct sockaddr *)&in6, "in6");

  exit (EXIT_SUCCESS);
}

void
print_addr (const struct sockaddr *addr, const char *prefix)
{
  printf ("%s -> sockaddr\n------------\n"
          "sa_family = 0x%0x, offset = %lu\n"
          "sa_data = %s, offset = %lu\n",
          prefix, addr->sa_family, offsetof (struct sockaddr, sa_family),
          addr->sa_data, offsetof (struct sockaddr, sa_data));
  if (addr->sa_family == AF_INET)
    {
      char ss[INET_ADDRSTRLEN];
      if (inet_ntop (addr->sa_family,
                     &((struct sockaddr_in *)addr)->sin_addr.s_addr, ss,
                     INET_ADDRSTRLEN))
        {
          printf ("%s:inet_ntop = %s\n", prefix, ss);
        }
    }
  else if (addr->sa_family == AF_INET6)
    {
      char ss[INET6_ADDRSTRLEN];
      if (inet_ntop (addr->sa_family,
                     &((struct sockaddr_in6 *)addr)->sin6_addr, ss,
                     INET6_ADDRSTRLEN))
        {
          printf ("%s:inet_ntop = %s\n", prefix, ss);
        }
    }
}
