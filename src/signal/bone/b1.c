#include "_signal_.h"
#include <pthread.h>

static void on_sig (int);
static void pr_pid (void);

int
main (void)
{
  sigset_t oset, nset;
  struct sigaction oact, nact;

  pr_pid ();

  /* examine current mask */
  assert (sigprocmask (SIG_BLOCK, NULL, &oset) == 0
          && "should return current mask");
  assert (oset == 0 && "sigset_t default should be zero");

  sigfillset (&nset);
  assert (sigismember (&nset, SIGABRT) == 1 && "SIGABRT should in set");

  sigemptyset (&nset);
  assert (nset == 0 && "should be zero");

  sigaddset (&nset, SIGABRT);
  assert (sigismember (&nset, SIGABRT) == 1 && "SIGABRT should in set");

  sigdelset (&nset, SIGABRT);
  assert (sigismember (&nset, SIGABRT) == 0 && "SIGABRT should not in set");

  /* block SIGABRT */
  sigemptyset (&nset);
  sigaddset (&nset, SIGABRT);
  assert (sigprocmask (SIG_SETMASK, &nset, &oset) == 0
          && "should block SIGABRT");
  raise (SIGABRT);
  /* reach here because SIGABRT had been blocked */

  nact.sa_handler = on_sig;
  nact.sa_flags = 0;
  nact.sa_mask = nset;
  assert (sigaction (SIGHUP, &nact, &oact) == 0 && "should on SIGHUP");
  raise (SIGABRT);
  /* reach here because SIGABRT steal been blocked */
  raise (SIGHUP);
  /* reach here because caught SIGHUP and return from signal handler */

  exit (0);
}

void
on_sig (int signo)
{
  assert (signo == SIGHUP && "should caught SIGHUP");
  pr_pid ();
}

void
pr_pid (void)
{
  fprintf (stderr, "pid=0x%zu tid=0x%zu\n", (size_t)getpid (),
           (size_t)pthread_self ());
}
