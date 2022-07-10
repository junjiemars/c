#include <_signal_.h>

static void _unused_(on_sig_int)(int);

int
main(int _unused_(argc), char ** _unused_(argv))
{
  sigset_t  nset, oset;

  setvbuf(stdout, NULL, _IONBF, 0);
  printf("%d\n", getpid());


  sigemptyset(&nset);
  sigaddset(&nset, SIGINT);

  if (sigprocmask(SIG_BLOCK, &nset, &oset))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("# critical region\n");

  if (sigprocmask(SIG_SETMASK, &oset, NULL))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("# before pause\n");

  pause();

  printf("# after pause\n");

  exit(EXIT_SUCCESS);
}

void
on_sig_int(int signo)
{
  if (SIGINT == signo)
    {
      printf("# %s\n", _str_(SIGINT));
    }
}
