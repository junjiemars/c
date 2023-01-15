#include "_signal_.h"
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>


/*
 * 1. `getpwnam(3)' is nonreentrant function because which using
 * static data struct inside.
 *
 * 2. `getpwnam(3)' may be blocked in on_sig_alrm after first call.
 *
 * 3. `getpwnam_r(3)' is reentrant function.
 *
 */


#define ALRM_N  8


static void  on_sig_alrm(int);

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

  if (signal(SIGALRM, on_sig_alrm) == SIG_ERR)
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
          printf("getpwnam_r(%s) = NULL at @ %s\n", username1, __FUNCTION__);
          continue;
        }
#else
      if ((p = getpwnam(username1)) == NULL)
        {
          printf("getpwnam(%s) = NULL at @ %s\n", username1, __FUNCTION__);
          continue;
        }

#endif  /* _REENTRANT_ */

      pause();

      /* may be interrupted by signal at here */

      if (strcmp(p->pw_name, username1) != 0)
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
  errno_t  saved_errno  =  errno;

  printf("# %s(%d) at %s\n", _str_(SIGALRM), signo, __FUNCTION__);

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
      printf("getpwnam_r(%s) = NULL at %s\n", username2, __FUNCTION__);
    }

#else
  struct passwd  *p;

  errno = 0;
  if ((p = getpwnam(username2)) == NULL)
    {
      printf("getpwnam(%s) = NULL at %s\n", username2, __FUNCTION__);
    }

#endif  /* _REENTRANT_ */


  alarm(1);

  errno = saved_errno;
}
