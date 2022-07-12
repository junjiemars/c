#include <_signal_.h>

/*
 * expect:
 *
 * 1. block specified signal before enter critical section.
 * 2. unblock the signal after leaving critical section.
 * 3. pause and wait the deferred signal.
 *
 */


static void on_sig_quit(int);


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

  if (SIG_ERR == signal(SIGINT, on_sig_quit))
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

  if (sigprocmask(SIG_SETMASK, &oset, NULL))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("! %s unblocked\n", _str_(SIGQUIT));

  /* race condition here */
  pause();

  printf("# exit\n");
  exit(EXIT_SUCCESS);
}


void
on_sig_quit(int signo)
{
  if (SIGQUIT == signo)
    {
      printf("# %s\n", _str_(SIGQUIT));
    }
}
