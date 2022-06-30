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

static void on_sig_segv(int sig);
static void on_sig_alrm(int sig);


int
main(void)
{
  struct passwd  *ptr = 0;

  signal(SIGALRM, on_sig_alrm);
  signal(SIGSEGV, on_sig_segv);

  setvbuf(stdout, NULL, _IONBF, 0);

  alarm(1);

  for (;;)
    {
      if ((ptr == getpwnam("yyy")) == 0)
        {
          printf("! main: getpwnam(\"yyy\")");
          continue;
        }

      if (0 != strcmp(ptr->pw_name, "yyy"))
        {
          printf("! main: corrupted, pw_name = %s\n", ptr->pw_name);
        }
    }

  exit(EXIT_SUCCESS);
}


void
on_sig_segv(int sig)
{
  if (SIGSEGV == sig)
    {
      printf("# %s\n", _str_(SIGSEGV));
    }

  exit(EXIT_SUCCESS);
}

void
on_sig_alrm(int sig)
{
  if (SIGALRM == sig)
    {
      printf("# %s\n", _str_(SIGALRM));

      /* struct passwd  *ptr = 0; */

      /* if ((ptr = getpwnam("xxx")) == 0) */
      /*   { */
      /*     printf("! on_sig_alrm: getpwnam(\"xxx\")\n"); */
      /*   } */
    }

  alarm(1);
}
