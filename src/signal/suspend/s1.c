#include <_signal_.h>

_unused_(static void on_sig_int(int));

int
main(void)
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
