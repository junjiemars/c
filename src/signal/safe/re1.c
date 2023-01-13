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


static void  on_sig_alrm(int);

static const char  *username1;
static const char  *username2;

static volatile int  alrm_count  =  ALRM_N;


int
main(int argc, char **argv)
{
  struct sigaction  act, oact;

  if (argc < 3)
    {
      printf("usage: %s <username1> <username2>\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  username1 = argv[1];
  username2 = argv[2];

  setvbuf(stdout, NULL, _IONBF, 0);
  printf("%d\n", getpid());

  act.sa_handler = on_sig_alrm;
  sigemptyset(&act.sa_mask);
  sigaddset(&act.sa_mask, SIGALRM);
  act.sa_flags = 0;

  if (sigaction(SIGALRM, &act, &oact) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

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
on_sig_alrm(int signo)
{
  printf("# %d) %s at %s\n", signo, _str_(SIGALRM), __FUNCTION__);

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
  sigset_t        mset;

  if (sigprocmask(SIG_BLOCK, NULL, &mset) == -1)
    {
      perror(NULL);
    }
  else
    {
      if (sigismember(&mset, signo) == 1)
        {
          printf("# %d) %s had been blocked at %s, we cannot go anymore\n",
                 signo, _str_(SIGALRM), __FUNCTION__);
          exit(EXIT_SUCCESS);
        }
    }

  errno = 0;
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



  alarm(1);
}
