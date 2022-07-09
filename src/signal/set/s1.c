#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#define STR(s)   #s
#define YES(s)   (s) ? "yes" : "no"

#define FMT_SIG  "%-16s %02i, %-4s\n"
#define FMT_SYM  "%-16s (no symbol)\n"


int main(void)
{
  int       rc;
  sigset_t  oset;

  sigprocmask(0, NULL, &oset);

#if defined(SIGHUP)
  {
     rc = sigismember(&oset, SIGHUP);
     printf(FMT_SIG, STR(SIGHUP), SIGHUP, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGHUP));
#endif

#if defined(SIGINT)
  {
     rc = sigismember(&oset, SIGINT);
     printf(FMT_SIG, STR(SIGINT), SIGINT, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGINT));
#endif

#if defined(SIGQUIT)
  {
     rc = sigismember(&oset, SIGQUIT);
     printf(FMT_SIG, STR(SIGQUIT), SIGQUIT, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGQUIT));
#endif

#if defined(SIGILL)
  {
     rc = sigismember(&oset, SIGILL);
     printf(FMT_SIG, STR(SIGILL), SIGILL, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGILL));
#endif

#if defined(SIGTRAP)
  {
     rc = sigismember(&oset, SIGTRAP);
     printf(FMT_SIG, STR(SIGTRAP), SIGTRAP, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGTRAP));
#endif

#if defined(SIGABRT)
  {
     rc = sigismember(&oset, SIGABRT);
     printf(FMT_SIG, STR(SIGABRT), SIGABRT, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGABRT));
#endif

#if defined(SIGPOLL)
  {
     rc = sigismember(&oset, SIGPOLL);
     printf(FMT_SIG, STR(SIGPOLL), SIGPOLL, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGPOLL));
#endif

#if defined(SIGIOT)
  {
     rc = sigismember(&oset, SIGIOT);
     printf(FMT_SIG, STR(SIGIOT), SIGIOT, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGIOT));
#endif

#if defined(SIGEMT)
  {
     rc = sigismember(&oset, SIGEMT);
     printf(FMT_SIG, STR(SIGEMT), SIGEMT, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGEMT));
#endif

#if defined(SIGFPE)
  {
     rc = sigismember(&oset, SIGFPE);
     printf(FMT_SIG, STR(SIGFPE), SIGFPE, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGFPE));
#endif

#if defined(SIGKILL)
  {
     rc = sigismember(&oset, SIGKILL);
     printf(FMT_SIG, STR(SIGKILL), SIGKILL, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGKILL));
#endif

#if defined(SIGBUS)
  {
     rc = sigismember(&oset, SIGBUS);
     printf(FMT_SIG, STR(SIGBUS), SIGBUS, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGBUS));
#endif

#if defined(SIGSEGV)
  {
     rc = sigismember(&oset, SIGSEGV);
     printf(FMT_SIG, STR(SIGSEGV), SIGSEGV, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGSEGV));
#endif

#if defined(SIGSYS)
  {
     rc = sigismember(&oset, SIGSYS);
     printf(FMT_SIG, STR(SIGSYS), SIGSYS, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGSYS));
#endif

#if defined(SIGPIPE)
  {
     rc = sigismember(&oset, SIGPIPE);
     printf(FMT_SIG, STR(SIGPIPE), SIGPIPE, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGPIPE));
#endif

#if defined(SIGALRM)
  {
     rc = sigismember(&oset, SIGALRM);
     printf(FMT_SIG, STR(SIGALRM), SIGALRM, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGALRM));
#endif

#if defined(SIGTERM)
  {
     rc = sigismember(&oset, SIGTERM);
     printf(FMT_SIG, STR(SIGTERM), SIGTERM, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGTERM));
#endif

#if defined(SIGURG)
  {
     rc = sigismember(&oset, SIGURG);
     printf(FMT_SIG, STR(SIGURG), SIGURG, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGURG));
#endif

#if defined(SIGSTOP)
  {
     rc = sigismember(&oset, SIGSTOP);
     printf(FMT_SIG, STR(SIGSTOP), SIGSTOP, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGSTOP));
#endif

#if defined(SIGTSTP)
  {
     rc = sigismember(&oset, SIGTSTP);
     printf(FMT_SIG, STR(SIGTSTP), SIGTSTP, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGTSTP));
#endif

#if defined(SIGCONT)
  {
     rc = sigismember(&oset, SIGCONT);
     printf(FMT_SIG, STR(SIGCONT), SIGCONT, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGCONT));
#endif

#if defined(SIGCHLD)
  {
     rc = sigismember(&oset, SIGCHLD);
     printf(FMT_SIG, STR(SIGCHLD), SIGCHLD, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGCHLD));
#endif

#if defined(SIGTTIN)
  {
     rc = sigismember(&oset, SIGTTIN);
     printf(FMT_SIG, STR(SIGTTIN), SIGTTIN, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGTTIN));
#endif

#if defined(SIGTTOU)
  {
     rc = sigismember(&oset, SIGTTOU);
     printf(FMT_SIG, STR(SIGTTOU), SIGTTOU, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGTTOU));
#endif

#if defined(SIGIO)
  {
     rc = sigismember(&oset, SIGIO);
     printf(FMT_SIG, STR(SIGIO), SIGIO, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGIO));
#endif

#if defined(SIGXCPU)
  {
     rc = sigismember(&oset, SIGXCPU);
     printf(FMT_SIG, STR(SIGXCPU), SIGXCPU, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGXCPU));
#endif

#if defined(SIGXFSZ)
  {
     rc = sigismember(&oset, SIGXFSZ);
     printf(FMT_SIG, STR(SIGXFSZ), SIGXFSZ, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGXFSZ));
#endif

#if defined(SIGVTALRM)
  {
     rc = sigismember(&oset, SIGVTALRM);
     printf(FMT_SIG, STR(SIGVTALRM), SIGVTALRM, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGVTALRM));
#endif

#if defined(SIGPROF)
  {
     rc = sigismember(&oset, SIGPROF);
     printf(FMT_SIG, STR(SIGPROF), SIGPROF, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGPROF));
#endif

#if defined(SIGWINCH)
  {
     rc = sigismember(&oset, SIGWINCH);
     printf(FMT_SIG, STR(SIGWINCH), SIGWINCH, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGWINCH));
#endif

#if defined(SIGINFO)
  {
     rc = sigismember(&oset, SIGINFO);
     printf(FMT_SIG, STR(SIGINFO), SIGINFO, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGINFO));
#endif

#if defined(SIGUSR1)
  {
     rc = sigismember(&oset, SIGUSR1);
     printf(FMT_SIG, STR(SIGUSR1), SIGUSR1, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGUSR1));
#endif

#if defined(SIGUSR2)
  {
     rc = sigismember(&oset, SIGUSR2);
     printf(FMT_SIG, STR(SIGUSR2), SIGUSR2, YES(rc));
  }
#else
  printf(FMT_SYM, STR(SIGUSR2));
#endif


  return 0;
}
