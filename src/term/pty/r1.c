#include "_term_.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <termios.h>

int
main (void)
{
  int fd;
  char *ss;
  struct termios term;

  if ((fd = posix_openpt (O_RDWR | O_NOCTTY)) == -1)
    {
      perror (NULL);
      exit (1);
    }

  if (grantpt (fd) == -1)
    {
      perror (NULL);
      exit (1);
    }

  if ((ss = ptsname (fd)) != NULL)
    {
      fprintf (stdout, "fd %d %s\n", fd, ss);
    }

  if (!isatty (fd))
    {
      fprintf (stderr, "isatty: not a tty\n");
      goto clean_exit;
    }

  if (tcgetattr (fd, &term) != 0)
    {
      if (errno == ENOTTY)
        {
          fprintf (stderr, "tcgetattr: not a tty\n");
        }
      else
        perror ("tcgetattr:");
      goto clean_exit;
    }

clean_exit:
  if (unlockpt (fd) == -1)
    {
      perror (NULL);
      exit (1);
    }

  exit (0);
}
