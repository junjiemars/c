#include "_signal_.h"

/*
 * 2nd: emulates POSIX `sleep(3)'.
 *
 */

unsigned int sleep (unsigned int);

static void on_sig_alrm (int);

unsigned int
sleep (unsigned int nsecs)
{
  int unslept;
  sigset_t nset, oset, wset;
  struct sigaction nact, oact;

  sigemptyset (&nact.sa_mask);
  nact.sa_handler = on_sig_alrm;
  nact.sa_flags = 0;
  sigaction (SIGALRM, &nact, &oact);

  sigemptyset (&nset);
  sigaddset (&nset, SIGALRM);
  sigprocmask (SIG_BLOCK, &nset, &oset);

  if (nsecs > 0)
    {
      alarm (nsecs);

      wset = oset;
      sigdelset (&wset, SIGALRM);

      sigsuspend (&wset);
    }

  unslept = alarm (0);

  sigaction (SIGALRM, &oact, NULL);
  sigprocmask (SIG_SETMASK, &oset, NULL);

  return unslept;
}

void
on_sig_alrm (int signo)
{
  (void)signo;
}
