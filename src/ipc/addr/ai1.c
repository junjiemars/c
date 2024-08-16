#include "_ipc_.h"

int
main (int argc, char **argv)
{
  int rc;
  struct addrinfo hints = {0};
  struct addrinfo *res;

  if (argc < 3)
    {
      fprintf (stderr, "usage: %s <address> <service>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  rc = getaddrinfo (argv[1], argv[2], &hints, &res);
  if (rc != 0)
    {
      fprintf (stderr, "%s\n", gai_strerror (rc));
      exit (EXIT_FAILURE);
    }

  for (struct addrinfo *ai = res; ai != 0; ai = ai->ai_next)
    {
      int sfd;

      sfd = socket (ai->ai_family, ai->ai_socktype, ai->ai_protocol);
      if (sfd < 0)
        {
          perror (0);
          continue;
        }

      rc = connect (sfd, ai->ai_addr, ai->ai_addrlen);
      if (rc < 0)
        {
          close (sfd);
          perror (0);
          continue;
        }

      close (sfd);
      printf ("connected\n");

      break;
    }

  freeaddrinfo (res);
  exit (EXIT_SUCCESS);
}
