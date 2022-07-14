#include <_signal_.h>

static void on_sig_usr(int);
_unused_(static void tell_wait(void));
_unused_(static void tell_parent(pid_t));
_unused_(static void wait_parent(void));
_unused_(static void tell_child(pid_t pid));
_unused_(static void wait_child(void));

static volatile sig_atomic_t  sflag;
static sigset_t               nset, oset, zset;

int
main(_unused_(int argc), _unused_(char **argv))
{
  exit(EXIT_SUCCESS);
}

void
on_sig_usr(_unused_(int signo))
{
  sflag = 0;
}

void
tell_wait(void)
{
  if (SIG_ERR == signal(SIGUSR1, on_sig_usr))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (SIG_ERR == signal(SIGUSR2, on_sig_usr))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  sigemptyset(&zset);
  sigemptyset(&nset);
  sigaddset(&nset, SIGUSR1);
  sigaddset(&nset, SIGUSR2);

  if (sigprocmask(SIG_BLOCK, &nset, &oset))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
}

void
tell_parent(pid_t pid)
{
  kill(pid, SIGUSR2);
}

void
wait_parent(void)
{
  while (sflag == 0)
    {
      sigsuspend(&zset);
    }
  sflag = 0;

  if (sigprocmask(SIG_SETMASK, &oset, NULL))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
}

void
tell_child(pid_t pid)
{
  kill(pid, SIGUSR1);
}

void
wait_child(void)
{
  while (sflag == 0)
    {
      sigsuspend(&zset);
    }
  sflag = 0;

  if (sigprocmask(SIG_SETMASK, &oset, NULL))
    {
      perror(NULL);
    }
}
