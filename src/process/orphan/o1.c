#include "_process_.h"
#include "nore.h"
#include <stdlib.h>

/*
 * 1. a process whose parent terminates is called an orphan and is
 * inherited by `init' process.
 *
 * 2. the newly orphaned process group should be sent `SIGHUP'
 * followed by `SIGCONT' by POSIX.1.
 *
 */

#define PS_CMD_FMT "ps -opid,ppid,state,tty,command -p%d"

static char ps_cmd[NM_LINE_MAX];

int
main (void)
{
  pid_t pid;

  setbuf (stdout, NULL);
  printf ("parent: pid=%d enter ...\n", getpid ());

  if ((pid = fork ()) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {

      printf ("child: pid=%d enter ...\n", getpid ());

      snprintf (ps_cmd, NM_LINE_MAX, PS_CMD_FMT, getpid ());
      putchar ('\n');

      if (system (ps_cmd) == -1)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }

      printf ("\nchild: pid=%d exit ...\n", getpid ());
      exit (EXIT_SUCCESS);
    }

  printf ("parent: pid=%d exit ...\n", pid);

  exit (EXIT_SUCCESS);
}
