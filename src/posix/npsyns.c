#include <npsyn.h>
#include <signal.h>

static void on_sig_usr (int sig);

static volatile sig_atomic_t sflag;
static sigset_t nmask, omask, zmask;

static void
on_sig_usr (__attribute__ ((unused)) int sig)
{
  sflag = 1;
}

int
need_wait (void)
{
  signal (SIGUSR1, on_sig_usr);
  signal (SIGUSR2, on_sig_usr);

  sigemptyset (&zmask);
  sigemptyset (&nmask);

  sigaddset (&nmask, SIGUSR1);
  sigaddset (&nmask, SIGUSR2);

  return sigprocmask (SIG_BLOCK, &nmask, &omask);
}

int
tell_parent (pid_t pid)
{
  return kill (pid, SIGUSR2);
}

int
tell_child (pid_t pid)
{
  return kill (pid, SIGUSR1);
}

int
wait_parent (void)
{
  while (sflag == 0)
    {
      sigsuspend (&zmask);
    }
  sflag = 0;

  return sigprocmask (SIG_SETMASK, &omask, NULL);
}

int
wait_child (void)
{
  while (sflag == 0)
    {
      sigsuspend (&zmask);
    }
  sflag = 0;

  return sigprocmask (SIG_SETMASK, &omask, NULL);
}
