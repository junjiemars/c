#include "_signal_.h"
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>

/*
 * 1. getpwnam is nonreentrant function because which using static
 * data struct inside.
 *
 * 2. getpwnam should be blocked in on_sig_alrm after first call if
 * there no printf ___ statement above the comment.
 *
 */


#if (_REENTRANT_)
#define ALRM_N  16
static int   count  =  ALRM_N;
#endif


static void on_sig_segv(int sig);
static void on_sig_alrm(int sig);

const char  *username1;
const char  *username2;


int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      printf("usage: %s <username1> <username2>\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  username1 = argv[1];
  username2 = argv[2];

  setvbuf(stdout, NULL, _IONBF, 0);

  printf("%d\n", getpid());

  signal(SIGALRM, on_sig_alrm);
  signal(SIGSEGV, on_sig_segv);

  alarm(1);

  for (;;)
    {
      struct passwd  *p  =  NULL;

#if (_REENTRANT_)
      char           *buf;
      struct passwd   pwd;

      buf = malloc(NM_GETPW_R_SIZE_MAX);

      if (getpwnam_r(username1, &pwd, buf, NM_GETPW_R_SIZE_MAX, &p))
        {
          perror(NULL);
          free(buf);
          continue;
        }
#else
      p = getpwnam(username1);
      if (errno)
        {
          perror(NULL);
          continue;
        }
      if (NULL == p)
        {
          continue;
        }
      /* printf("# ___\n"); */

#endif

      /* may be interrupted by signal at here */

      if (0 != strcmp(p->pw_name, username1))
        {
          printf("! corrupted: expect <%s> but got <%s>\n",
                 username1, p->pw_name);
          break;
        }

#if (_REENTRANT_)
      free(buf);

#endif

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
      __attribute__((unused)) struct passwd  *p  =  0;
      printf("# %s\n", _str_(SIGALRM));

      /* wipped out the result of previous getpwnam call */

#if (_REENTRANT_)

      if (--count < 1)
        {
          printf("# exceed %s=%d\n", _str_(ALRM_N), ALRM_N);
          exit(EXIT_SUCCESS);
        }

      char           *buf;
      struct passwd   pwd;

      buf = malloc(NM_GETPW_R_SIZE_MAX);

      if (getpwnam_r(username2, &pwd, buf, NM_GETPW_R_SIZE_MAX, &p))
        {
          perror(NULL);
        }

      free(buf);

#else
      p = getpwnam(username2);
      if (errno)
        {
          perror(NULL);
        }

#endif

    }

  alarm(1);
}
