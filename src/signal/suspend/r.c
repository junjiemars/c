#include <_signal_.h>

static void on_sig_int(int);

static int  N  =  1;


int
main(int argc, char **argv)
{
  sigset_t  nset, oset;

  if (argc > 1)
    {
      N = atoi(argv[1]);
    }

  setvbuf(stdout, NULL, _IONBF, 0);
  printf("%d\n", getpid());

  if (SIG_ERR == signal(SIGINT, on_sig_int))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  sigemptyset(&nset);
  sigaddset(&nset, SIGINT);

  printf("! enter...\n");

  if (sigprocmask(SIG_BLOCK, &nset, &oset))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  sleep(N);

  printf("! leaved\n");

  if (-1 == sigsuspend(&nset))
    {
      if (errno)
        {
          perror(NULL);
        }
    }

  if (sigprocmask(SIG_SETMASK, &oset, NULL))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }



  sleep(N);

  printf("# exit\n");
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
