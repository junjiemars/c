#include "_ipc_.h"

int
main (int argc, char **argv)
{
  int fd;
  int size;
  const char *sock_file;
  struct sockaddr_un un;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <filename>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  sock_file = argv[1];

  /* avoid address alreay used */
  unlink (sock_file);

  un.sun_family = AF_UNIX;
  strcpy (un.sun_path, sock_file);
  if ((fd = socket (AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  /* intptr_t offsetof1 = (intptr_t)&((struct sockaddr_un *)0)->sun_path; */

  size = offsetof (struct sockaddr_un, sun_path) + strlen (un.sun_path);
  if (bind (fd, (struct sockaddr *)&un, size) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("!bound\n");

  exit (EXIT_SUCCESS);
}
