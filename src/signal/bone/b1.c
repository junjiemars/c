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
  assert (sigprocmask (0, NULL, &oset) == 0 && "should return current mask");
  assert (*(unsigned long *)&oset == 0 && "sigset_t default should be zero");

  sigfillset (&nset);
#if !(LINUX)
  assert ((unsigned long)nset == 0 && "should be full");
#endif  /* ! LINUX */
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
  assert (sigprocmask (SIG_SETMASK, &nset, NULL) == 0
          && "should block SIGABRT");
  raise (SIGABRT);
  /* reach here because SIGABRT had been blocked */
  assert (sigpending (&pset) == 0 && "should return pending mask");
  assert (sigismember (&pset, SIGABRT) == 1 && "SIGABRT should in set");

  nact.sa_handler = on_sig;
  nact.sa_flags = 0;
  nact.sa_mask = nset;
  assert (sigaction (SIGHUP, &nact, &oact) == 0 && "should on SIGHUP");
  raise (SIGABRT);
  /* reach here because SIGABRT steal been blocked */
  raise (SIGHUP);
  /* reach here because SIGHUP been caught and return from signal hander */

  sigemptyset (&pset);
  sigprocmask (SIG_BLOCK, NULL, &pset);
  assert (*(unsigned long*)&nset == *(unsigned long*)&pset && "should unchanged");

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
