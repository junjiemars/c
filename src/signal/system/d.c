#include "_signal_.h"

/*
 * `system(3)' driver.
 *
 */


extern int  system(const char *);

static void  on_sig_int(int);
static void  on_sig_chld(int);

static char  command[PATH_MAX];

int
main(int argc, char **argv)
{
  int  rc;

  if (argc > 1)
    {
      strcpy(command, argv[1]);
    }

  printf("%d\n", getpid());

  signal(SIGINT, on_sig_int);
  signal(SIGCHLD, on_sig_chld);

  printf("! system(\"%s\")\n", command);

  rc = system(command);

  printf("! return %d\n", rc);

  exit(rc);
}

void
on_sig_int(int signo)
{
  printf("# %s(%d)\n", _str_(SIGINT), signo);
}

void
on_sig_chld(int signo)
{
  printf("# %s(%d)\n", _str_(SIGCHLD), signo);
}
