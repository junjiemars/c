#include "psync.h"
#include <signal.h>

static void on_sig_usr (int);

static sigset_t nset, oset, zset;
static volatile sig_atomic_t sflag;

int
tell_wait (void)
{
  if (SIG_ERR == signal (SIGUSR1, on_sig_usr))
    {
      return -1;
    }
  if (SIG_ERR == signal (SIGUSR2, on_sig_usr))
    {
      return -1;
    }

  sigemptyset (&zset);
  sigemptyset (&nset);
  sigaddset (&nset, SIGUSR1);
  sigaddset (&nset, SIGUSR2);

  if (sigprocmask (SIG_BLOCK, &nset, &oset) == -1)
    {
      return -1;
    }
  return 0;
}

int inline
tell_parent (pid_t pid)
{
  return kill (pid, SIGUSR2);
}

int
wait_parent (void)
{
  while (sflag == 0)
    {
      sigsuspend (&zset);
    }
  sflag = 0;

  if (sigprocmask (SIG_SETMASK, &oset, NULL) == -1)
    {
      return -1;
    }
  return 0;
}

int inline
tell_child (pid_t pid)
{
  return kill (pid, SIGUSR1);
}

int
wait_child (void)
{
  while (sflag == 0)
    {
      sigsuspend (&zset);
    }
  sflag = 0;

  if (sigprocmask (SIG_SETMASK, &oset, NULL) == -1)
    {
      return -1;
    }
  return 0;
}

void
on_sig_usr (int signo)
{
  if (signo == SIGUSR1 || signo == SIGUSR2)
    {
      sflag = 1;
    }
}
