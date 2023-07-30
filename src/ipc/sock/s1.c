#include <_ipc_.h>
#include <sys/socket.h>
#include <sys/un.h>

int
main (void)
{
  int fd;
  int size;
  struct sockaddr_un un;

  un.sun_family = AF_UNIX;
  strcpy (un.sun_path, "hi.socket");
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
