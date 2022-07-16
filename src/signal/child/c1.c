#include <_signal_.h>
#include <sys/types.h>
#include <sys/wait.h>

static void on_sig_chld(int);

static int  N  =  5;

int
main(int argc, char **argv)
{
  pid_t  pid;

  printf("%d\n", getpid());

  if (argc > 1)
    {
      N = atoi(argv[1]);
    }

  if (SIG_ERR == signal(SIGCHLD, on_sig_chld))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  pid = fork();
  if (-1 == pid)
    {
      perror(NULL);
    }
  else if (0 == pid)
    {
      sleep(N);
      _exit(0);
    }

  pause();

  exit(EXIT_SUCCESS);
}


void
on_sig_chld(int signo)
{
  pid_t  pid;
  int    status;

  if (SIGCHLD == signo)
    {
      if (SIG_ERR == signal(SIGCHLD, on_sig_chld))
        {
          perror(NULL);
        }

      if (-1 == (pid = wait(&status)))
        {
          perror(NULL);
        }

      printf("# %s %d\n", _str_(SIGCHLD), pid);
    }
}
