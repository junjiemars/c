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

static void on_sig_segv(int sig);
static void on_sig_alrm(int sig);

const char  *username1;
const char  *username2;


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
      if (NULL == (p = getpwnam(username1)))
        {
          if (errno)
            {
              perror(NULL);
            }
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
  struct passwd  *p  =  NULL;

  if (SIGALRM == sig)
    {
      printf("# %s\n", _str_(SIGALRM));

      if (NULL == (p = getpwnam(username2)))
        {
          /* wipped out the result of previous getpwnam call */
        }
    }

  alarm(1);
}
