#include "_ipc_.h"

int
main (int argc, char **argv)
{
  int sfd;
  int status = 0;
  char *node;
  uint16_t port;
  struct sockaddr_in in4 = { 0 };

  if (argc < 3)
    {
      fprintf (stderr, "usage: %s <node> <port>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  node = argv[1];
  sscanf (argv[2], "%hu", &port);

  in4.sin_family = AF_INET;
  in4.sin_port = htons (port);
  in4.sin_addr.s_addr = inet_addr (node);

  sfd = socket (AF_INET, SOCK_STREAM, 0);
  if (sfd == -1)
    {
      perror (0);
      exit (EXIT_FAILURE);
    }

  if (connect (sfd, (struct sockaddr *)&in4, sizeof (in4)) < 0)
    {
      status = errno;
      perror (0);
      goto clean_exit;
    }

  printf ("XXX\n");

 clean_exit:
  close (sfd);
  exit (status);
}
