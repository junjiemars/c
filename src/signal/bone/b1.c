#include "_signal_.h"
#include <pthread.h>

static void on_sig (int);

static volatile pid_t pid;
static volatile pthread_t tid;


int
main (void)
{
  sigset_t oset, nset, pset;
  struct sigaction oact, nact;

  pid = getpid ();
  tid = pthread_self ();

  /* examine current mask */
  assert (sigprocmask (SIG_BLOCK, NULL, &oset) == 0
          && "should return current mask");
  assert (*(unsigned long *)&oset == 0 && "sigset_t default should be zero");

  sigfillset (&nset);
  assert ((unsigned long)(~nset) == 0 && "should be full");
  assert (sigismember (&nset, SIGABRT) == 1 && "SIGABRT should in set");

  sigemptyset (&nset);
  assert (*(unsigned long *)&nset == 0 && "should be zero");

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
  /* reach here because caught SIGHUP and then return from signal handler */

  sigprocmask (SIG_BLOCK, NULL, &pset);
  assert (nset == pset && "should unchanged");

  exit (0);
}

void
on_sig (int signo)
{
  pid_t pid1 = getpid ();
  pthread_t tid1 = pthread_self ();

  assert (pid == pid1 && tid == tid1 && "should same pid and tid");
  assert (signo == SIGHUP && "should caught SIGHUP");
}
