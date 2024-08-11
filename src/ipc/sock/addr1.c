#include "_ipc_.h"

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
  char in4_addr_ss[128] = "127.0.0.1";
  in4.sin_addr.s_addr = inet_addr (in4_addr_ss);
  struct in_addr in4_addr = { 0 };
  inet_pton (AF_INET, in4_addr_ss, &in4_addr);
  assert (in4.sin_addr.s_addr == in4_addr.s_addr);
  pr_addr ((struct sockaddr *)&in4, "in4");
  printf ("in4.sin_addr.s_addr = %s\n", inet_ntoa (in4.sin_addr));
  char in4_addr_ss1[128] = { 0 };
  inet_ntop (AF_INET, &in4.sin_addr.s_addr, in4_addr_ss1,
             sizeof (in4_addr_ss1));
  assert (strcmp (in4_addr_ss, in4_addr_ss1) == 0);

  /* internet v6 address */
  struct sockaddr_in6 in6 = { 0 };
  in6.sin6_family = AF_INET6;
  in6.sin6_port = 0x1234;
  struct in6_addr in6_addr_n;
  char in6_addr_ss[128] = { 0 };
  strcpy (in6_addr_ss, "240e:3a2:e7f:1410:84eb:7d13:9c3a:e7f5");
  inet_pton (AF_INET6, in6_addr_ss, &in6_addr_n);
  in6.sin6_addr = in6_addr_n;
  pr_addr ((struct sockaddr *)&in6, "in6");
  inet_ntop (AF_INET6, &in6.sin6_addr, in6_addr_ss, sizeof (in6_addr_ss));
  printf ("in6.sin6_addr = %s\n", in6_addr_ss);

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
