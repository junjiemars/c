#include "_ipc_.h"

int
main (int argc, char **argv)
{
  int sfd;
  struct sockaddr_in in4;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <node>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  sfd = socket (AF_INET, SOCK_STREAM, 0);
  if (sfd == 1)
    {
      err (EXIT_FAILURE);
    }

  in4.sin_family = AF_INET;
  in4.sin_port = htons (80);
  in4.sin_addr.s_addr = inet_addr (argv[1]);




  exit (EXIT_FAILURE);
}
