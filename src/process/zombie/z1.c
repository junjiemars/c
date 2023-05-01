#include "_process_.h"

/*
 * 1. On Linux, a child that terminates but had not been waited for
 * becomes a zombie.
 *
 * 2. On Darwin,
 *
 */

#define PS_CMD "ps -opid,ppid,state,command"
#define N_CHLD 5

static char cmd[NM_LINE_MAX];

int
main (int argc, char *argv[])
{
  int n, stat;
  pid_t pid;

  n = N_CHLD;
  if (argc >= 2)
    {
      n = atoi (argv[1]);
    }

  setbuf (stdout, NULL);
  printf ("# parent pid=%d\n", getpid ());

  for (int i = 0; i < n; i++)
    {
      if ((pid = fork ()) == -1)
        {
          perror (0);
          exit (errno);
        }

      if (pid == 0)
        {
          printf ("# child pid=%d\n", getpid ());
          exit (EXIT_SUCCESS);
        }

      /* only wait odd ones, the even ones should be zombies */
      if ((pid & 1) == 1)
        {
          waitpid (pid, &stat, 0);
          printf ("# child pid=%d exit(%d)\n", pid, stat);
        }
      else
        {
          snprintf (cmd, NM_LINE_MAX, PS_CMD " -p %d", pid);
          system (cmd);
        }
    }

  exit (EXIT_SUCCESS);
}
