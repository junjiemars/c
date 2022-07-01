#include "_signal_.h"
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>

/*
 * getpwnam is nonreentrant function because which using static data
 * struct inside.
 *
 */

#define ALRM_N  16

static void on_sig_segv(int sig);
static void on_sig_alrm(int sig);
static struct passwd *fn(const char *name);

const char  *username1;
const char  *username2;
static int  count  =  ALRM_N;


#if (_REENTRANT_)
char  pwdbuf[NM_GETPW_R_SIZE_MAX];

#endif


int
main(int argc, char **argv)
{
  struct passwd  *p  =  NULL;

  if (argc < 3)
    {
      printf("usage: %s <username1> <username2>\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  username1 = argv[1];
  username2 = argv[2];

  signal(SIGALRM, on_sig_alrm);
  signal(SIGSEGV, on_sig_segv);

  setvbuf(stdout, NULL, _IONBF, 0);

  alarm(1);

  for (;;)
    {
      errno = 0;
      p = fn(username1);
      if (NULL == p)
        {
          continue;
        }

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
      printf("# %s\n", _str_(SIGALRM));

      if (count-- <= 0)
        {
          printf("# exceed %s=%d\n", _str_(ALRM_N), ALRM_N);
          exit(EXIT_SUCCESS);
        }

#if (_REENTRANT_)

#else
      /* wipped out the result of previous getpwnam call */
      (void *) fn(username2);

#endif

    }


  alarm(1);
}

struct passwd*
fn(const char *name)
{
  struct passwd  *p  =  0;

  errno = 0;

#if (_REENTRANT_)
  struct passwd  pwd;

  if (getpwnam_r(name, &pwd, pwdbuf, sizeof(pwdbuf), &p))
    {
      perror(NULL);
    }

#else
  if (NULL == (p = getpwnam(name)))
    {
      if (errno)
        {
          perror(NULL);
        }
    }

#endif

  return p;
}
