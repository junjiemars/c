#include "../_ipc_.h"

static void print_addr (const struct sockaddr *, const char *);

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

  struct addrinfo hint = { 0 };
  /* IPv4: www.example.com http */
  struct addrinfo *w4;
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  if (getaddrinfo ("www.example.com", "http", &hint, &w4) != 0)
    {
      fprintf (stderr, "%s\n", gai_strerror (errno));
    }
  print_addr (w4->ai_addr, "http");
  freeaddrinfo (w4);

  /* IPv4: www.example.com http */
  struct addrinfo *w6;
  hint.ai_family = AF_INET6;
  hint.ai_socktype = SOCK_STREAM;
  if (getaddrinfo ("www.example.com", "http", &hint, &w6) != 0)
    {
      fprintf (stderr, "%s\n", gai_strerror (errno));
    }
  print_addr (w6->ai_addr, "http");
  freeaddrinfo (w6);

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
      struct sockaddr_in *in4 = (struct sockaddr_in *)addr;
      if (inet_ntop (addr->sa_family, &in4->sin_addr, ss, INET_ADDRSTRLEN))
        {
          printf ("sin_addr = %s, port = %hu\n", ss, ntohs (in4->sin_port));
        }
    }
  else if (addr->sa_family == AF_INET6)
    {
      char ss[INET6_ADDRSTRLEN];
      struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)addr;
      if (inet_ntop (addr->sa_family, &in6->sin6_addr, ss, INET6_ADDRSTRLEN))
        {
          printf ("sin6_addr = %s, port = %hu\n", ss, ntohs (in6->sin6_port));
        }
    }
}
