#include "_term_.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int
main (void)
{
  int ldisc;
  int fd = STDIN_FILENO;

  if (ioctl (fd, TIOCGETD, &ldisc) == -1)
    {
      perror (NULL);
      exit (1);
    }

#if !(LINUX)
  switch (ldisc)
    {
    case TTYDISC:
      printf ("fd %d %s(%d)\n", fd, _str_ (TTYDISC), ldisc);
      break;
    case TABLDISC:
      printf ("fd %d %s(%d)\n", fd, _str_ (TABLDISC), ldisc);
      break;
    case SLIPDISC:
      printf ("fd %d %s(%d)\n", fd, _str_ (SLIPDISC), ldisc);
      break;
    case PPPDISC:
      printf ("fd %d %s(%d)\n", fd, _str_ (PPPDISC), ldisc);
      break;
    default:
      printf ("fd %d %s(%d)\n", fd, "Unknown", ldisc);
      break;
    }
#endif /* end of LINUX */

  exit (0);
}
