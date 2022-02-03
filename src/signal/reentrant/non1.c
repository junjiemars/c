#include "_signal_.h"
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>

/*
 * 1. getpwnam is nonreentrant function.
 * 2. usually, the program would be terminated by a SIGSEGV signal.
 *
 */

static void on_sig_segv(int signo);
static void on_sig_alrm(int signo);

static void
on_sig_segv(int signo)
{
  _unused_(signo);
  fprintf(stderr, "#on_sig_segv\n");
  exit(0);
}

static void
on_sig_alrm(int signo)
{
  struct passwd  *ptr = 0;

  _unused_(signo);

  fprintf(stderr, "#on_sig_alrm\n");

  if ((ptr = getpwnam("xxx")) == 0)
    {
      fprintf(stderr, "!on_sig_alrm: getpwnam(\"xxx\")\n");
    }

  alarm(1);
}


int
main(void)
{
  struct passwd  *ptr = 0;

  signal(SIGALRM, on_sig_alrm);
  signal(SIGSEGV, on_sig_segv);

  alarm(1);

  for (;;)
    {
      if ((ptr == getpwnam("yyy")) == 0)
        {
          fprintf(stderr, "!main: getpwnam(\"yyy\")");
          continue;
        }

      if (0 != strcmp(ptr->pw_name, "yyy"))
        {
          fprintf(stderr, "!main: corrupted, pw_name = %s\n", ptr->pw_name);
        }
    }

  return 0;
}
