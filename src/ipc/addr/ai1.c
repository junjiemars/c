#include "_ipc_.h"

static void print_addrinfo (const struct addrinfo *);

int
main (int argc, char **argv)
{
  int rc;
  struct addrinfo hints = { 0 };
  struct addrinfo *ais;

  if (argc < 3)
    {
      fprintf (stderr, "usage: %s <node> <service>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  hints.ai_flags = AI_CANONNAME;
  rc = getaddrinfo (argv[1], argv[2], &hints, &ais);
  if (rc != 0)
    {
      err (EXIT_FAILURE, "getaddrinfo error: %s", gai_strerror (rc));
    }

  for (struct addrinfo *ai = ais; ai != 0; ai = ai->ai_next)
    {
      print_addrinfo (ai);
      printf ("------------\n");
    }

  exit (EXIT_SUCCESS);
}

void
print_addrinfo (const struct addrinfo *ai)
{
  /* flags */
  printf ("flags:");
  if (ai->ai_flags == 0)
    {
      printf (" 0");
    }
  else if ((ai->ai_flags & AI_PASSIVE) == AI_PASSIVE)
    {
      printf (" %s(%i)", _str_ (AI_PASSIVE), AI_PASSIVE);
    }
  else if ((ai->ai_flags & AI_CANONNAME) == AI_CANONNAME)
    {
      printf (" %s(%i)", _str_ (AI_CANONNAME), AI_CANONNAME);
    }
  else if ((ai->ai_flags & AI_NUMERICHOST) == AI_NUMERICHOST)
    {
      printf (" %s(%i)", _str_ (AI_NUMERICHOST), AI_NUMERICHOST);
    }
  else if ((ai->ai_flags & AI_NUMERICSERV) == AI_NUMERICSERV)
    {
      printf (" %s(%i)", _str_ (AI_NUMERICSERV), AI_NUMERICSERV);
    }
  else if ((ai->ai_flags & AI_V4MAPPED) == AI_V4MAPPED)
    {
      printf (" %s(%i)", _str_ (AI_V4MAPPED), AI_V4MAPPED);
    }
  else if ((ai->ai_flags & AI_ALL) == AI_ALL)
    {
      printf (" %s(%i)", _str_ (AI_ALL), AI_ALL);
    }
  printf ("\n");

  /* family */
  printf ("family:");
  switch (ai->ai_family)
    {
    case AF_INET:
      printf (" %s(%i)", _str_ (AF_INET), AF_INET);
      break;
    case AF_INET6:
      printf (" %s(%i)", _str_ (AF_INET6), AF_INET6);
      break;
    case AF_UNIX:
      printf (" %s(%i)", _str_ (AF_UNIX), AF_UNIX);
      break;
    case AF_UNSPEC:
      printf (" %s(%i)", _str_ (AF_UNSPEC), AF_UNSPEC);
      break;
    default:
      printf (" unknown (%d)", ai->ai_family);
      break;
    }
  printf ("\n");

  /* socket type */
  printf ("socktype:");
  switch (ai->ai_socktype)
    {
    case SOCK_STREAM:
      printf (" %s(%i)", _str_ (SOCK_STREAM), SOCK_STREAM);
      break;
    case SOCK_DGRAM:
      printf (" %s(%i)", _str_ (SOCK_DGRAM), SOCK_DGRAM);
      break;
    case SOCK_SEQPACKET:
      printf (" %s(%i)", _str_ (SOCK_SEQPACKET), SOCK_SEQPACKET);
      break;
    case SOCK_RAW:
      printf (" %s(%i)", _str_ (SOCK_RAW), SOCK_RAW);
      break;
    default:
      printf (" unknown(%i)", ai->ai_socktype);
      break;
    }
  printf ("\n");

  /* protocol */
  printf ("protocol:");
  switch (ai->ai_protocol)
    {
    case 0:
      printf (" (0)");
      break;
    case IPPROTO_TCP:
      printf (" %s(%i)", _str_ (IPPROTO_TCP), IPPROTO_TCP);
      break;
    case IPPROTO_UDP:
      printf (" %s(%i)", _str_ (IPPROTO_UDP), IPPROTO_UDP);
      break;
    case IPPROTO_RAW:
      printf (" %s(%i)", _str_ (IPPROTO_RAW), IPPROTO_RAW);
      break;
    default:
      printf (" unknown(%i)", ai->ai_protocol);
      break;
    }
  printf ("\n");

  /* host */
  printf ("host: %s\n", ai->ai_canonname ? ai->ai_canonname : "-");

  /* inet4 */
  if (ai->ai_family == AF_INET)
    {
      char ss[INET_ADDRSTRLEN];
      struct sockaddr_in *in4 = (struct sockaddr_in *)ai->ai_addr;
      const char *addr
          = inet_ntop (AF_INET, &in4->sin_addr, ss, INET_ADDRSTRLEN);
      printf ("address: %s\n", addr ? addr : "unknown");
      printf ("port: %d\n", ntohs (in4->sin_port));
    }

  /* inet6 */
  if (ai->ai_family == AF_INET6)
    {
      char ss[INET6_ADDRSTRLEN];
      struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)ai->ai_addr;
      const char *addr
          = inet_ntop (AF_INET, &in6->sin6_addr, ss, INET6_ADDRSTRLEN);
      printf ("address: %s\n", addr ? addr : "unknown");
      printf ("port: %d\n", ntohs (in6->sin6_port));
    }
}
