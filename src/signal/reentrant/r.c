#include "_signal_.h"
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>


/*
 * 1. `getpwnam(3)' is nonreentrant function because which using
 * static data struct inside.
 *
 * 2. `getpwnam(3)' should be blocked in on_sig_alrm after first call
 * if there no printf ___ statement above the comment.
 *
 */


#define ALRM_N  16


static void on_sig_segv(int sig);
static void on_sig_alrm(int sig);

static const char  *username1;
static const char  *username2;

static volatile int  alrm_count  =  ALRM_N;


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
      struct passwd  pwd;
      char           buf[NM_GETPW_R_SIZE_MAX];

      if (getpwnam_r(username1, &pwd, buf, NM_GETPW_R_SIZE_MAX, &p))
        {
          perror(NULL);
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
          printf("getpwnam(...) = NULL at @ %s\n", __FUNCTION__);
          continue;
        }
      /* printf("# ___\n"); */

#endif  /* _REENTRANT_ */

      /* may be interrupted by signal at here */

      if (0 != strcmp(p->pw_name, username1))
        {
          printf("! corrupted: expect <%s> but got <%s>\n",
                 username1, p->pw_name);
          break;
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
      printf("# %s at %s\n", _str_(SIGALRM), __FUNCTION__);

      /* wipped out the result of previous getpwnam call */

      if (--alrm_count < 1)
        {
          printf("# exceed %s=%d\n", _str_(ALRM_N), ALRM_N);
          exit(EXIT_SUCCESS);
        }

#if (_REENTRANT_)

      struct passwd  pwd, *p = NULL;
      static char    buf[NM_GETPW_R_SIZE_MAX];

      if (getpwnam_r(username2, &pwd, buf, NM_GETPW_R_SIZE_MAX, &p))
        {
          perror(NULL);
        }

#else
      struct passwd  *p;
      sigset_t        oset;

      if (sigprocmask(SIG_BLOCK, NULL, &oset) < 0)
        {
          perror(NULL);
        }
      else
        {
          if (sigismember(&oset, SIGALRM) == 1)
            {
              printf("blocked %s at %s, so we cannot go anymore\n",
                     _str_(SIGALRM), __FUNCTION__);
              exit(EXIT_SUCCESS);
            }
        }

      p = getpwnam(username2);
      if (errno)
        {
          perror(NULL);
        }
      if (p == NULL)
        {
          printf("getpwnam(...) = NULL at %s\n", __FUNCTION__);
        }

#endif  /* _REENTRANT_ */

    }

  alarm(1);
}
