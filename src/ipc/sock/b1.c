#include "_ipc_.h"

int
main (int argc, char **argv)
{
  int fd;
  int size;
  struct sockaddr_un un;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <filename>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  un.sun_family = AF_UNIX;
  strcpy (un.sun_path, argv[1]);
  if ((fd = socket (AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  size = offsetof (struct sockaddr_un, sun_path) + strlen (un.sun_path);
  if (bind (fd, (struct sockaddr *)&un, size) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("!bound\n");

  exit (EXIT_SUCCESS);
}
