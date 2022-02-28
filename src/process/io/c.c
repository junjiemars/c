#include "_process_.h"
#include <stdio.h>


#if (_SYNC_)

static volatile sig_atomic_t  sflag;
static sigset_t               nmask, omask, zmask;

static void on_sig_usr(int signo);
static void tell_wait(void);

static void tell_parent(pid_t pid);

static void wait_child(void);


#endif  /* _SYNC_ */


static void char_attime(const char *ss);


int
main(void)
{
  pid_t  pid;

#if (_SYNC_)
  tell_wait();

#endif  /* _SYNC_ */


  pid = fork();
  if (pid == -1)
    {
      perror("!panic:");
      return 1;
    }

  if (pid == 0)
    {
      char_attime("output from child\n");

#if (_SYNC_)
      tell_parent(getppid());

#endif  /* _SYNC_ */

    }
  else
    {

#if (_SYNC_)
      wait_child();

#endif  /* _SYNC_ */

      char_attime("output from parent\n");
    }

  return 0;
}

#if (_SYNC_)

static void
on_sig_usr(int signo)
{
  _unused_(signo);

  sflag = 1;
}

static void
tell_wait(void)
{
  signal(SIGUSR1, on_sig_usr);
  signal(SIGUSR2, on_sig_usr);

  sigemptyset(&zmask);
  sigemptyset(&nmask);

  sigaddset(&nmask, SIGUSR1);
  sigaddset(&nmask, SIGUSR2);

  sigprocmask(SIG_BLOCK, &nmask, &omask);
}

static void
tell_parent(pid_t pid)
{
  kill(pid, SIGUSR2);
}


static void
wait_child(void)
{
  while (sflag == 0)
    {
      sigsuspend(&zmask);
    }
  sflag = 0;

  sigprocmask(SIG_SETMASK, &omask, NULL);
}


#endif  /* _SYNC_ */


static void
char_attime(const char *ss)
{
  int          c;
  const char  *s;

  setbuf(stdout, NULL);

  for (s = ss; (c = *s++) != 0;)
    {
      putc(c, stdout);
    }
}
