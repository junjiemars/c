#include "_process_.h"

/*
 * 1. a process whose parent terminates is called an orphan and is
 * inherited by `init' process.
 *
 * 2. the newly orphaned process group should be sent `SIGHUP'
 * followed by `SIGCONT' by POSIX.1.
 *
 */

static void  on_sig_hup(int);
static void  pr_ids(const char *);


static int  N  =  0;

int
main(int argc, char *argv[])
{
  pid_t  pid;

  if (argc > 1)
    {
      N = atoi(argv[1]);
    }

  pr_ids("parent");

  if ((pid = fork()) < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      char  c;

      pr_ids("child");

      if (signal(SIGHUP, on_sig_hup) == SIG_ERR)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
      kill(getpid(), SIGTSTP);

      pr_ids("child");

      if (read(STDIN_FILENO, &c, 1) != 1)
        {
          int  err = errno;
          fprintf(stderr, "# read failed(%d): %s\n", (int) err, strerror(err));
        }
    }
  else
    {
      sleep(N);
    }


  exit(EXIT_SUCCESS);
}


void
on_sig_hup(int signo)
{
  if (signo == SIGHUP)
    {
      fprintf(stderr, "# %s(%d) caught(%d)\n", _str_(SIGHUP), signo, getpid());
    }
}

void
pr_ids(const char *who)
{
  fprintf(stderr, "%-10s: pid=%d, ppid=%d, pgrp=%d, tpgrp=%d\n", who,
          getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
}
