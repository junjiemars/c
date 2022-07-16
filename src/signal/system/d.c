#include <_signal_.h>

extern int system(const char *);

static void on_sig_int(int);
static void on_sig_chld(int);

static char  cmd[PATH_MAX];

int
main(int argc, char **argv)
{
  int  rc;

  if (argc > 1)
    {
      strcpy(cmd, argv[1]);
    }

  printf("%d\n", getpid());

  signal(SIGINT, on_sig_int);
  signal(SIGCHLD, on_sig_chld);

  rc = system(cmd);
  printf("! return %d\n", rc);

  exit(rc);
}

void
on_sig_int(int signo)
{
  if (SIGINT == signo)
    {
      printf("# %s\n", _str_(SIGINT));
    }
}

void
on_sig_chld(int signo)
{
  if (SIGCHLD == signo)
    {
      printf("# %s\n", _str_(SIGCHLD));
    }
}
