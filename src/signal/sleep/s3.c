#include "_signal_.h"
#include <setjmp.h>


/*
 * 3th: emulates POSIX `sleep(3)'.
 *
 */


unsigned int  sleep(unsigned int);


unsigned int
sleep(unsigned int nsecs)
{
  sigset_t          nset, oset, sset;
  struct sigaction  nact, oact;

  sigemptyset(&nact.sa_mask);
  nact.sa_handler = on_sig_alrm;
  nact.sa_flags = 0;
  sigaction(SIGALRM, &nact, &oact);

  sigemptyset(&nset);
  sigaddset(&nset, SIGALRM);
  sigprocmask(SIG_BLOCK, &nset, &oset);

  alarm(nsecs);
  sset = oset;
  sigdelset(&sset, SIGALRM);

  sigsuspend(&sset);

  unslept = alarm(0);

  sigaction(SIGALRM, &oact, NULL);
  sigprocmask(SIG_SETMASK, &oset, NULL);

  return unslept;
}
