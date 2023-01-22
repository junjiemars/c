#include "_process_.h"


#if (_WITH_SYNC_)

static volatile sig_atomic_t  sflag;
static sigset_t               nmask, omask, zmask;

static void on_sig_usr(int sig);
static void need_wait(void);
static void tell_parent(pid_t pid);
static void wait_child(void);

#endif  /* _WITH_SYNC_ */


static void out(const char *ss);


int
main(void)
{
  pid_t  pid;

#if (_WITH_SYNC_)
  need_wait();

#endif  /* _WITH_SYNC_ */


  pid = fork();
  if (pid == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      out("# output from child\n");

#if (_WITH_SYNC_)
      tell_parent(getppid());

#endif  /* _WITH_SYNC_ */

    }
  else
    {

#if (_WITH_SYNC_)
      wait_child();

#endif  /* _WITH_SYNC_ */

      out("# output from parent\n");
    }

  exit(EXIT_SUCCESS);
}


#if (_WITH_SYNC_)

static void
on_sig_usr(__attribute__((unused)) int sig)
{
  sflag = 1;
}

static void
need_wait(void)
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


#endif  /* _WITH_SYNC_ */


static void
out(const char *ss)
{
  int          c;
  const char  *s;

  /* unbuffered */
  setvbuf(stdout, NULL, _IONBF, 0);

  for (s = ss; (c = *s++) != 0;)
    {
      putc(c, stdout);
    }
}
