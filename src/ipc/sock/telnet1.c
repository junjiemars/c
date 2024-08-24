#include "_ipc_.h"

int
main (int argc, char **argv)
{
  int sfd;
  int status = 0;
  char *node, *service = 0;
  struct addrinfo hint = { 0 }, *in4;

  if (argc < 3)
    {
      fprintf (stderr, "usage: %s <node> [service]\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  node = argv[1];
  service = argv[2];

  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  /* hint.ai_protocol = IPPROTO_TCP; */

  if (getaddrinfo (node, service, &hint, &in4) != 0)
    {
      status = errno;
      fprintf (stderr, "%s\n", gai_strerror (status));
      goto clean_exit;
    }

  if ((sfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      status = errno;
      perror (0);
      goto clean_addr;
    }

  if (connect (sfd, in4->ai_addr, in4->ai_addrlen) < 0)
    {
      status = errno;
      if (status != ECONNREFUSED)
        {
          perror (0);
          goto clean_sock;
        }
    }

  printf ("#successed\n");

clean_sock:
  close (sfd);
clean_addr:
  freeaddrinfo (in4);
clean_exit:
  exit (status);
}
